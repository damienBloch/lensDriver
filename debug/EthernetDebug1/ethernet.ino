//#include"ethernet.h"
//
//void Ethernet::init(void)
//{     
//   //reset W5500
//   ETH_RSTX_PORT->PIO_PER |= ETH_RSTX_MSK;
//   ETH_RSTX_PORT->PIO_OER |= ETH_RSTX_MSK;
//   ETH_RSTX_PORT->PIO_CODR |= ETH_RSTX_MSK;
//   delay(10);
//   ETH_RSTX_PORT->PIO_SODR |= ETH_RSTX_MSK;
//   delay(10);
//
//   //initialise W5500 CSX pin 
//   ETH_CSX_PORT->PIO_PER |= ETH_CSX_MSK;
//   ETH_CSX_PORT->PIO_OER |= ETH_CSX_MSK;
//   ETH_CSX_PORT->PIO_SODR |= ETH_CSX_MSK; 
//}
