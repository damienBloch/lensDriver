Parameters configuration;
DueFlashStorage dueFlashStorage;

__attribute__ ((section (".ramfunc")))
void _EEFC_ReadUniqueID( unsigned int * pdwUniqueID )
{
    unsigned int status ;
 
    /* Send the Start Read unique Identifier command (STUI) by writing the Flash Command Register with the STUI command.*/
    EFC1->EEFC_FCR = (0x5A << 24) | EFC_FCMD_STUI;
    do
    {
        status = EFC1->EEFC_FSR ;
    } while ( (status & EEFC_FSR_FRDY) == EEFC_FSR_FRDY ) ;

    /* The Unique Identifier is located in the first 128 bits of the Flash memory mapping. So, at the address 0x400000-0x400003. */
    pdwUniqueID[0] = *(uint32_t *)IFLASH1_ADDR;
    pdwUniqueID[1] = *(uint32_t *)(IFLASH1_ADDR + 4);
    pdwUniqueID[2] = *(uint32_t *)(IFLASH1_ADDR + 8);
    pdwUniqueID[3] = *(uint32_t *)(IFLASH1_ADDR + 12);

    /* To stop the Unique Identifier mode, the user needs to send the Stop Read unique Identifier
       command (SPUI) by writing the Flash Command Register with the SPUI command. */
    EFC1->EEFC_FCR = (0x5A << 24) | EFC_FCMD_SPUI ;

    /* When the Stop read Unique Unique Identifier command (SPUI) has been performed, the
       FRDY bit in the Flash Programming Status Register (EEFC_FSR) rises. */
    do
    {
        status = EFC1->EEFC_FSR ;
    } while ( (status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY ) ;
}

void systemPreset(void)
{  
  byte b[sizeof(Parameters)]; 
  memcpy(b, &defaultParameters, sizeof(Parameters)); 
  __set_FAULTMASK(1);
  dueFlashStorage.write(PARAMETERS_ADDRESS, b, sizeof(Parameters));
  __set_FAULTMASK(0);
}

Parameters loadParameters()
{
  byte* b = dueFlashStorage.readAddress(PARAMETERS_ADDRESS); 
  Parameters parametersFromFlash; 
  memcpy(&parametersFromFlash, b, sizeof(Parameters));
  return parametersFromFlash;
}

void storeParameters(Parameters parameters)
{
  byte b[sizeof(Parameters)]; 
  memcpy(b, &parameters, sizeof(Parameters)); 
  __set_FAULTMASK(1);
  dueFlashStorage.write(PARAMETERS_ADDRESS, b, sizeof(Parameters));
  __set_FAULTMASK(0);
}

void resetCPU(void)
{
  if(SerialUSB)
    SerialUSB.flush();
  RSTC->RSTC_CR=RSTC_CR_KEY(0xA5) | RSTC_CR_PROCRST | RSTC_CR_PERRST |RSTC_CR_EXTRST;
}
