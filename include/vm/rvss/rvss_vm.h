/**
 * @file rvss_vm.h
 * @brief RVSS VM definition
 * @author Vishank Singh, https://github.com/VishankSingh
 */
#ifndef RVSS_VM_H
#define RVSS_VM_H


#include "vm/vm_base.h"

#include "rvss_control_unit.h"

#include <stack>
#include <vector>
#include <iostream>
#include <cstdint>

// TODO: use a circular buffer instead of a stack for undo/redo

struct RegisterChange {
  unsigned int reg_index;
  unsigned int reg_type; // 0 for GPR, 1 for CSR, 2 for FPR
  uint64_t old_value;
  uint64_t new_value;
};

struct MemoryChange {
  uint64_t address;
  std::vector<uint8_t> old_bytes_vec; 
  std::vector<uint8_t> new_bytes_vec; 
};

struct StepDelta {
  uint64_t old_pc;
  uint64_t new_pc;
  std::vector<RegisterChange> register_changes;
  std::vector<MemoryChange> memory_changes;
};


// class RingUndoRedo {
//   std::vector<StepDelta> buffer_;
//   int current_;      // index of current state
//   int size_;         // number of valid entries
//   int head_;
//   const int capacity_;

//  public:
//   explicit RingUndoRedo(int cap)
//     : buffer_(cap), current_(-1), size_(0), head_(-1), capacity_(cap) {}

//   void push(const StepDelta& delta) {
//     head_ = (head_ + 1) % capacity_;
//     buffer_[head_] = delta;
//     current_ = head_;  // move current to new step

//     if (size_ < capacity_)
//         size_++;
//     else {
//         ; // overwrite oldest entry
//     }

//     // Invalidate all redos beyond head_
//     int i = (head_ + 1) % capacity_;
//     while (i != current_) {
//         buffer_[i] = StepDelta(); // or mark invalid
//         i = (i + 1) % capacity_;
//     }
// }


//   bool can_undo() const {
//     return size_ > 0 && current_ != -1;
//   }

//   bool can_redo() const {
//     return current_ != head_ && !buffer_[(current_ + 1) % capacity_].register_changes.empty();
// }

//   StepDelta undo() {
//     if (!can_undo()) throw std::runtime_error("Nothing to undo");
//     StepDelta delta = buffer_[current_];
//     current_ = (current_ - 1 + capacity_) % capacity_;
//     return delta;
//   }

//   StepDelta redo() {
//     if (!can_redo()) throw std::runtime_error("Nothing to redo");

//     current_ = (current_ + 1) % capacity_;
//     return buffer_[current_];
// }
// };




class RVSSVM : public VmBase {
 public:
  RVSSControlUnit control_unit_;
  std::atomic<bool> stop_requested_ = false;


  std::stack<StepDelta> undo_stack_;
  std::stack<StepDelta> redo_stack_;
  // RingUndoRedo history_{1000}; // or however many steps you want to store

  StepDelta current_delta_;

  // intermediate variables
  int64_t execution_result_{};
  int64_t memory_result_{};
  // int64_t memory_address_{};
  // int64_t memory_data_{};
  uint64_t return_address_{};

  bool branch_flag_ = false;
  int64_t next_pc_{}; // for jal, jalr,

  // CSR intermediate variables
  uint16_t csr_target_address_{};
  uint64_t csr_old_value_{};
  uint64_t csr_write_val_{};
  uint8_t csr_uimm_{};

  void Fetch();

  void Decode();

  void Execute();
  void ExecuteFloat();
  void ExecuteBFloat16();
  void ExecuteDouble();
  void ExecuteCsr();
  void HandleSyscall();

  void WriteMemory();
  void WriteMemoryFloat();
  void WriteMemoryDouble();

  void WriteBack();
  void WriteBackFloat();
  void WriteBackDouble();
  void WriteBackCsr();

  RVSSVM();
  ~RVSSVM();

  void Run() override;
  void DebugRun() override;
  void Step() override;
  void Undo() override;
  void Redo() override;
  void Reset() override;

  void RequestStop() {
    stop_requested_ = true;
  }

  bool IsStopRequested() const {
    return stop_requested_;
  }
  
  void ClearStop() {
    stop_requested_ = false;
  }

  void PrintType() {
    std::cout << "rvssvm" << std::endl;
  }
};

#endif // RVSS_VM_H
