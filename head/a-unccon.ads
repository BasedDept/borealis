--  @file a-unccon.ads
--  @brief Unchecked Type Conversions
--  @author George Witt
--  @date 2024-03-02
--
--  ISO/IEC 8652:1995 13.9
--
--  Copyright (c) 1992-1995 Intermetrics, Inc.
--  Copyright (c) 2024 George Witt
--  SPDX-License-Identifier:

generic
   type Source (<>) is limited private;
   type Target (<>) is limited private;

function Ada.Unchecked_Conversion (S : Source) return Target;

pragma No_Elaboration_Code_All (Ada.Unchecked_Conversion);
pragma Pure (Ada.Unchecked_Conversion);
pragma Import (Intrinsic, Ada.Unchecked_Conversion);
