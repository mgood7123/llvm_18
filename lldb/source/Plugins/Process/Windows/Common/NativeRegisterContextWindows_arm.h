//===-- NativeRegisterContextWindows_arm.h ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#if defined(__arm__) || defined(_M_ARM)
#ifndef liblldb_NativeRegisterContextWindows_arm_h_
#define liblldb_NativeRegisterContextWindows_arm_h_

#include "Plugins/Process/Utility/lldb-arm-register-enums.h"

#include "NativeRegisterContextWindows.h"

namespace lldb_private {

class NativeThreadWindows;

class NativeRegisterContextWindows_arm : public NativeRegisterContextWindows {
public:
  NativeRegisterContextWindows_arm(const ArchSpec &target_arch,
                                   NativeThreadProtocol &native_thread);

  uint32_t GetRegisterSetCount() const override;

  const RegisterSet *GetRegisterSet(uint32_t set_index) const override;

  Status ReadRegister(const RegisterInfo *reg_info,
                      RegisterValue &reg_value) override;

  Status WriteRegister(const RegisterInfo *reg_info,
                       const RegisterValue &reg_value) override;

  Status ReadAllRegisterValues(lldb::WritableDataBufferSP &data_sp) override;

  Status WriteAllRegisterValues(const lldb::DataBufferSP &data_sp) override;

  Status IsWatchpointHit(uint32_t wp_index, bool &is_hit) override;

  Status GetWatchpointHitIndex(uint32_t &wp_index,
                               lldb::addr_t trap_addr) override;

  Status IsWatchpointVacant(uint32_t wp_index, bool &is_vacant) override;

  bool ClearHardwareWatchpoint(uint32_t wp_index) override;

  Status ClearAllHardwareWatchpoints() override;

  Status SetHardwareWatchpointWithIndex(lldb::addr_t addr, size_t size,
                                        uint32_t watch_flags,
                                        uint32_t wp_index);

  uint32_t SetHardwareWatchpoint(lldb::addr_t addr, size_t size,
                                 uint32_t watch_flags) override;

  lldb::addr_t GetWatchpointAddress(uint32_t wp_index) override;

  uint32_t NumSupportedHardwareWatchpoints() override;

protected:
  Status GPRRead(const uint32_t reg, RegisterValue &reg_value);

  Status GPRWrite(const uint32_t reg, const RegisterValue &reg_value);

  Status FPRRead(const uint32_t reg, RegisterValue &reg_value);

  Status FPRWrite(const uint32_t reg, const RegisterValue &reg_value);

private:
  bool IsGPR(uint32_t reg_index) const;

  bool IsFPR(uint32_t reg_index) const;
};

} // namespace lldb_private

#endif // liblldb_NativeRegisterContextWindows_arm_h_
#endif // defined(__arm__) || defined(_M_ARM)
