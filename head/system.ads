--  @file system.ads
--  @brief The Package System
--  @author George Witt
--  @date 2024-03-02
--
--  ISO/IEC 8652:1995 13.7
--
--  Copyright (c) 2024 George Witt
--  SPDX-License-Identifier: BSD-2-Clause

package System is
   pragma Pure;
   pragma No_Elaboration_Code_All;
   type Name is (SYSTEM_NAME_GNAT);
   System_Name : constant Name := SYSTEM_NAME_GNAT;

   Min_Int             : constant := -2 ** (Standard'Max_Integer_Size - 1);
   Max_Int             : constant :=  2 ** (Standard'Max_Integer_Size - 1) - 1;

   Max_Binary_Modulus    : constant := 2 ** Standard'Max_Integer_Size;
   Max_Nonbinary_Modulus : constant := 2 ** Integer'Size - 1;

   Max_Base_Digits       : constant := Long_Long_Float'Digits;
   Max_Digits            : constant := Long_Long_Float'Digits;

   Max_Mantissa          : constant := Standard'Max_Integer_Size - 1;
   Fine_Delta            : constant := 2.0 ** (-Max_Mantissa);

   Tick                  : constant := 0.000_001;

   type Address is private;
   pragma Preelaborable_Initialization (Address);
   Null_Address : constant Address;

   Storage_Unit : constant := 8;
   Word_Size    : constant := Standard'Word_Size;
   Memory_Size  : constant := 2 ** Word_Size;

   function "<"  (Left, Right : Address) return Boolean;
   pragma Import (Intrinsic, "<");
   function "<=" (Left, Right : Address) return Boolean;
   pragma Import (Intrinsic, "<=");
   function ">"  (Left, Right : Address) return Boolean;
   pragma Import (Intrinsic, ">");
   function ">=" (Left, Right : Address) return Boolean;
   pragma Import (Intrinsic, ">=");
   function "="  (Left, Right : Address) return Boolean;
   pragma Import (Intrinsic, "=");

   type Bit_Order is (High_Order_First, Low_Order_First);
   Default_Bit_Order : constant Bit_Order := Low_Order_First;
   pragma Warnings (Off, Default_Bit_Order);

   subtype Any_Priority       is Integer      range  0 .. 31;
   subtype Priority           is Any_Priority range  0 .. 30;
   subtype Interrupt_Priority is Any_Priority range 31 .. 31;

   Default_Priority : constant Priority := 15;
   Max_Priority           : constant Positive := 30;
   Max_Interrupt_Priority : constant Positive := 31;

private
   Run_Time_Name : constant String := "Northern Lights Runtime";
   type Address is mod Memory_Size;
   Null_Address : constant Address := 0;

   Backend_Divide_Checks     : constant Boolean := False;
   Backend_Overflow_Checks   : constant Boolean := True;
   Command_Line_Args         : constant Boolean := False;
   Configurable_Run_Time     : constant Boolean := True;
   Denorm                    : constant Boolean := True;
   Duration_32_Bits          : constant Boolean := False;
   Exit_Status_Supported     : constant Boolean := False;
   Machine_Overflows         : constant Boolean := False;
   Machine_Rounds            : constant Boolean := True;
   Preallocated_Stacks       : constant Boolean := False;
   Signed_Zeros              : constant Boolean := True;
   Stack_Check_Default       : constant Boolean := False;
   Stack_Check_Probes        : constant Boolean := False;
   Stack_Check_Limits        : constant Boolean := False;
   Support_Aggregates        : constant Boolean := True;
   Support_Composite_Assign  : constant Boolean := True;
   Support_Composite_Compare : constant Boolean := True;
   Support_Long_Shifts       : constant Boolean := True;
   Always_Compatible_Rep     : constant Boolean := False;
   Suppress_Standard_Library : constant Boolean := False;
   Use_Ada_Main_Program_Name : constant Boolean := False;
   ZCX_By_Default            : constant Boolean := False;

end System;
