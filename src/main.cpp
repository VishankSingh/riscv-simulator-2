#include "main.h"
#include "assembler/assembler.h"
#include "utils.h"
#include "globals.h"
#include "vm/rvss/rvss_vm.h"
#include "vm_runner.h"
#include "command_handler.h"
#include "config.h"

#include <iostream>
#include <thread>
#include <bitset>
#include <regex>



int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cerr << "No arguments provided. Use --help for usage information.\n";
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--help" || arg == "-h") {
        std::cout << "Usage: " << argv[0] << " [options]\n"
                  << "Options:\n"
                  << "  --help, -h           Show this help message\n"
                  << "  --assemble <file>    Assemble the specified file\n"
                  << "  --run <file>         Run the specified file\n"
                  << "  --verbose-errors     Enable verbose error printing\n"
                  << "  --start-vm           Start the VM with the default program\n"
                  << "  --start-vm --vm-as-backend  Start the VM with the default program in backend mode\n";
        return 0;

    } else if (arg == "--assemble") {
        if (++i >= argc) {
            std::cerr << "Error: No file specified for assembly.\n";
            return 1;
        }
        try {
            AssembledProgram program = assemble(argv[i]);
            std::cout << "Assembled program: " << program.filename << '\n';
            return 0;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }

    } else if (arg == "--run") {
        if (++i >= argc) {
            std::cerr << "Error: No file specified to run.\n";
            return 1;
        }
        try {
            AssembledProgram program = assemble(argv[i]);
            RVSSVM vm;
            vm.LoadProgram(program);
            vm.Run();
            std::cout << "Program running: " << program.filename << '\n';
            return 0;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }

    } else if (arg == "--verbose-errors") {
        globals::verbose_errors_print = true;
        std::cout << "Verbose error printing enabled.\n";

    } else if (arg == "--vm-as-backend") {
        globals::vm_as_backend = true;
        std::cout << "VM backend mode enabled.\n";
    } else if (arg == "--start-vm") {
        break;

    } else {
        std::cerr << "Unknown option: " << arg << '\n';
        return 1;
    }
  }
  


  setupVmStateDirectory();



  AssembledProgram program;
  RVSSVM vm;
  // try {
  //   program = assemble("/home/vis/Desk/codes/assembler/examples/ntest1.s");
  // } catch (const std::runtime_error &e) {
  //   std::cerr << e.what() << '\n';
  //   return 0;
  // }

  // std::cout << "Program: " << program.filename << std::endl;

  // unsigned int count = 0;
  // for (const uint32_t &instruction : program.text_buffer) {
  //     std::cout << std::bitset<32>(instruction)
  //               << " | "
  //               << std::setw(8) << std::setfill('0') << std::hex << instruction
  //               << " | "
  //               << std::setw(0) << count
  //               << std::dec << "\n";
  //     count += 4;
  // }

  // vm.LoadProgram(program);
  

  std::cout << "VM_STARTED" << std::endl;
  // std::cout << globals::invokation_path << std::endl;

  std::thread vm_thread;
  bool vm_running = false;

  auto launch_vm_thread = [&](auto fn) {
    if (vm_thread.joinable()) {
      vm.RequestStop();   
      vm_thread.join();
    }
    vm_running = true;
    vm_thread = std::thread([&]() {
      fn();               
      vm_running = false;
    });
  };




  std::string command_buffer;
  while (true) {
    // std::cout << "=> ";
    std::getline(std::cin, command_buffer);
    command_handler::Command command = command_handler::ParseCommand(command_buffer);

    if (command.type==command_handler::CommandType::MODIFY_CONFIG) {
      if (command.args.size() != 3) {
        std::cout << "VM_MODIFY_CONFIG_ERROR" << std::endl;
        continue;
      }
      try {
        vm_config::config.modifyConfig(command.args[0], command.args[1], command.args[2]);
        std::cout << "VM_MODIFY_CONFIG_SUCCESS" << std::endl;
      } catch (const std::exception &e) {
        std::cout << "VM_MODIFY_CONFIG_ERROR" << std::endl;
        std::cerr << e.what() << '\n';
        continue;
      }
      continue;
    }



    if (command.type==command_handler::CommandType::LOAD) {
      try {
        program = assemble(command.args[0]);
        std::cout << "VM_PARSE_SUCCESS" << std::endl;
        vm.output_status_ = "VM_PARSE_SUCCESS";
        vm.DumpState(globals::vm_state_dump_file_path);
      } catch (const std::runtime_error &e) {
        std::cout << "VM_PARSE_ERROR" << std::endl;
        vm.output_status_ = "VM_PARSE_ERROR";
        vm.DumpState(globals::vm_state_dump_file_path);
        std::cerr << e.what() << '\n';
        continue;
      }
      vm.LoadProgram(program);
      std::cout << "Program loaded: " << command.args[0] << std::endl;
    } else if (command.type==command_handler::CommandType::RUN) {
      launch_vm_thread([&]() { vm.Run(); });
    } else if (command.type==command_handler::CommandType::DEBUG_RUN) {
      launch_vm_thread([&]() { vm.DebugRun(); });
    } else if (command.type==command_handler::CommandType::STOP) {
      vm.RequestStop();
      std::cout << "VM_STOPPED" << std::endl;
      vm.output_status_ = "VM_STOPPED";
      vm.DumpState(globals::vm_state_dump_file_path);
    } else if (command.type==command_handler::CommandType::STEP) {
      if (vm_running) continue;
      launch_vm_thread([&]() { vm.Step(); });

    } else if (command.type==command_handler::CommandType::UNDO) {
      if (vm_running) continue;
      vm.Undo();
    } else if (command.type==command_handler::CommandType::REDO) {
      if (vm_running) continue;
      vm.Redo();
    } else if (command.type==command_handler::CommandType::RESET) {
      vm.Reset();
    } else if (command.type==command_handler::CommandType::EXIT) {
      vm.RequestStop();
      if (vm_thread.joinable()) vm_thread.join(); // ensure clean exit
      vm.output_status_ = "VM_EXITED";
      vm.DumpState(globals::vm_state_dump_file_path);
      break;
    } else if (command.type==command_handler::CommandType::ADD_BREAKPOINT) {
      vm.AddBreakpoint(std::stoul(command.args[0], nullptr, 10));
    } else if (command.type==command_handler::CommandType::REMOVE_BREAKPOINT) {
      vm.RemoveBreakpoint(std::stoul(command.args[0], nullptr, 10));
    } else if (command.type==command_handler::CommandType::MODIFY_REGISTER) {
      try {
        if (command.args.size() != 2) {
          std::cout << "VM_MODIFY_REGISTER_ERROR" << std::endl;
          continue;
        }
        std::string reg_name = command.args[0];
        uint64_t value = std::stoull(command.args[1], nullptr, 16);
        vm.ModifyRegister(reg_name, value);
        DumpRegisters(globals::registers_dump_file_path, vm.registers_);
        std::cout << "VM_MODIFY_REGISTER_SUCCESS" << std::endl;
      } catch (const std::out_of_range &e) {
        std::cout << "VM_MODIFY_REGISTER_ERROR" << std::endl;
        continue;
      } catch (const std::exception& e) {
        std::cout << "VM_MODIFY_REGISTER_ERROR" << std::endl;
        continue;
      }
    } else if (command.type==command_handler::CommandType::GET_REGISTER) {
      std::string reg_str = command.args[0];
      if (reg_str[0] == 'x') {
        std::cout << "VM_REGISTER_VAL_START";
        std::cout << "0x"
                  << std::hex
                  << vm.registers_.ReadGpr(std::stoi(reg_str.substr(1))) 
                  << std::dec;
        std::cout << "VM_REGISTER_VAL_END"<< std::endl;
      } 
      else if (reg_str[0] == 'f') {
        std::cout << "VM_REGISTER_VAL_START";
        std::cout << "0x"
                  << std::hex
                  << vm.registers_.ReadFpr(std::stoi(reg_str.substr(1))) 
                  << std::dec;
        std::cout << "VM_REGISTER_VAL_END"<< std::endl;
      }
      
    }

  
    else if (command.type==command_handler::CommandType::MODIFY_MEMORY) {
      if (command.args.size() != 3) {
        std::cout << "VM_MODIFY_MEMORY_ERROR" << std::endl;
        continue;
      }
      try {
        uint64_t address = std::stoull(command.args[0], nullptr, 16);
        std::string type = command.args[1];
        uint64_t value = std::stoull(command.args[2], nullptr, 16);

        if (type == "byte") {
          vm.memory_controller_.WriteByte(address, static_cast<uint8_t>(value));
        } else if (type == "half") {
          vm.memory_controller_.WriteHalfWord(address, static_cast<uint16_t>(value));
        } else if (type == "word") {
          vm.memory_controller_.WriteWord(address, static_cast<uint32_t>(value));
        } else if (type == "double") {
          vm.memory_controller_.WriteDoubleWord(address, value);
        } else {
          std::cout << "VM_MODIFY_MEMORY_ERROR" << std::endl;
          continue;
        }
        std::cout << "VM_MODIFY_MEMORY_SUCCESS" << std::endl;
      } catch (const std::out_of_range &e) {
        std::cout << "VM_MODIFY_MEMORY_ERROR" << std::endl;
        continue;
      } catch (const std::exception& e) {
        std::cout << "VM_MODIFY_MEMORY_ERROR" << std::endl;
        continue;
      }
    }
    
    
    
    else if (command.type==command_handler::CommandType::DUMP_MEMORY) {
      try {
        vm.memory_controller_.DumpMemory(command.args);
      } catch (const std::out_of_range &e) {
        std::cout << "VM_MEMORY_DUMP_ERROR" << std::endl;
        continue;
      } catch (const std::exception& e) {
        std::cout << "VM_MEMORY_DUMP_ERROR" << std::endl;
        continue;
      }
    } else if (command.type==command_handler::CommandType::PRINT_MEMORY) {
      for (size_t i = 0; i < command.args.size(); i+=2) {
        uint64_t address = std::stoull(command.args[i], nullptr, 16);
        uint64_t rows = std::stoull(command.args[i+1]);
        vm.memory_controller_.PrintMemory(address, rows);
      }
      std::cout << std::endl;
    } else if (command.type==command_handler::CommandType::GET_MEMORY_POINT) {
      if (command.args.size() != 1) {
        std::cout << "VM_GET_MEMORY_POINT_ERROR" << std::endl;
        continue;
      }
      // uint64_t address = std::stoull(command.args[0], nullptr, 16);
      vm.memory_controller_.GetMemoryPoint(command.args[0]);
    } 


    else if (command.type==command_handler::CommandType::VM_STDIN) {
      vm.PushInput(command.args[0]);
    }
    
    
    else if (command.type==command_handler::CommandType::DUMP_CACHE) {
      std::cout << "Cache dumped." << std::endl;
    } else {
      std::cout << "Invalid command.";
      std::cout << command_buffer << std::endl;
    }

  }






  return 0;
}