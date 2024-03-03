--  @file s-stalib.adb
--  @brief GNAT Standard Library Stub
--  @author George Witt
--  @date 2024-03-02
--
--  Copyright (c) 2024 George Witt
--  SPDX-License-Identifier: BSD-2-Clause

package body System.Standard_Library is

   Runtime_Finalized : Boolean := False;

   procedure Adafinal is
   begin
      if not Runtime_Finalized then
         Runtime_Finalized := True;
      end if;
   end Adafinal;

end System.Standard_Library;
