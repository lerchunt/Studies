/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#include "dma_testbench.h"
#include "pv_memory.h"
#include "pv_router.h"
#include "pv_dma.h"


int sc_main(int argc , char **argv) {

  static const tlm::tlm_endianness SOC_ENDIAN = tlm::TLM_LITTLE_ENDIAN;
  //static const tlm::tlm_endianness SOC_ENDIAN = tlm::TLM_BIG_ENDIAN;

  sc_signal<bool> pv_dma_irq;
  dma_testbench testbench("testbench",SOC_ENDIAN,0x4000);
  pv_memory memory1("memory1",0x100,SOC_ENDIAN,true);
  pv_memory memory2("memory2",0x100,SOC_ENDIAN);
  pv_dma dma("dma",SOC_ENDIAN);
  pv_router<int,int> router("router");

  // inclure ici les connexions des composants

  sc_start();

  return 0;

}



/* END of main.cpp */
