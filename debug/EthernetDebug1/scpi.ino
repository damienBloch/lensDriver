#include"scpi.h"

extern Parameters configuration;

void SCPI::init(void)
{
  //create the SCPI tree and assign callback function for each command
  scpi_init(&ctx);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*IDN?", 5, "*IDN?", 5, identify);
  temperature = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "TEMPERATURE", 11, "TEMP", 4, NULL);
    scpi_register_command(temperature, SCPI_CL_CHILD, "MEASURE?", 8, "MEAS?", 5, measure_temperature);
    pid = scpi_register_command(temperature, SCPI_CL_CHILD, "PID", 3, "PID", 3, NULL);
      scpi_register_command(pid, SCPI_CL_CHILD, "P?", 2, "P?", 2, get_P);
      scpi_register_command(pid, SCPI_CL_CHILD, "P", 1, "P", 1, set_P);
      scpi_register_command(pid, SCPI_CL_CHILD, "I?", 2, "I?", 2, get_I);
      scpi_register_command(pid, SCPI_CL_CHILD, "I", 1, "I", 1, set_I);
      scpi_register_command(pid, SCPI_CL_CHILD, "D?", 2, "D?", 2, get_D);
      scpi_register_command(pid, SCPI_CL_CHILD, "D", 1, "D", 1, set_D);
      scpi_register_command(pid, SCPI_CL_CHILD, "SETPOINT?", 9, "SET?", 4, get_setpoint);
      scpi_register_command(pid, SCPI_CL_CHILD, "SETPOINT", 8, "SET", 3, set_setpoint);
      scpi_register_command(pid, SCPI_CL_CHILD, "OUTPUT?", 7, "OUT?", 4, get_output);
      scpi_register_command(pid, SCPI_CL_CHILD, "RESET", 5, "RES", 3, reset_temperature);
      pid_limit = scpi_register_command(pid, SCPI_CL_CHILD, "LIMIT", 5, "LIM", 3, NULL);
        scpi_register_command(pid_limit, SCPI_CL_CHILD, "MINIMUM?", 8, "MIN?", 4, get_pid_minimum);
        scpi_register_command(pid_limit, SCPI_CL_CHILD, "MAXIMUM?", 8, "MAX?", 4, get_pid_maximum);
        scpi_register_command(pid_limit, SCPI_CL_CHILD, "MINIMUM", 7, "MIN", 3, set_pid_minimum);
        scpi_register_command(pid_limit, SCPI_CL_CHILD, "MAXIMUM", 7, "MAX", 3, set_pid_maximum);
  source = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "SOURCE", 6, "SOURCE", 6, NULL);
    scpi_register_command(source, SCPI_CL_CHILD, "CURRENT", 7, "CUR", 3, set_current);
    scpi_register_command(source, SCPI_CL_CHILD, "CURRENT?", 8, "CUR?", 4, get_current);
    current_limit = scpi_register_command(source, SCPI_CL_CHILD, "LIMIT", 5, "LIM", 3, NULL);
      scpi_register_command(current_limit, SCPI_CL_CHILD, "MAXIMUM?", 9, "MAX?", 4, get_currentMax);
      scpi_register_command(current_limit, SCPI_CL_CHILD, "MAXIMUM", 8, "MAX", 3, set_currentMax);
      scpi_register_command(current_limit, SCPI_CL_CHILD, "MINIMUM?", 9, "MIN?", 4, get_currentMin);
      scpi_register_command(current_limit, SCPI_CL_CHILD, "MINIMUM", 8, "MIN", 3, set_currentMin);
    arbitrary = scpi_register_command(source, SCPI_CL_CHILD, "ARBITRARY", 9, "ARB", 3, NULL);
      scpi_register_command(arbitrary, SCPI_CL_CHILD, "SEQUENCE", 8, "SEQ", 3, set_sequence);
      scpi_register_command(arbitrary, SCPI_CL_CHILD, "SEQUENCE?", 9, "SEQ?", 4, get_sequence);
      scpi_register_command(arbitrary, SCPI_CL_CHILD, "FREQUENCY", 9, "FREQ", 4, set_frequency);
      scpi_register_command(arbitrary, SCPI_CL_CHILD, "FREQUENCY?", 10, "FREQ?", 5, get_frequency);
    scpi_register_command(source, SCPI_CL_CHILD, "MODE?", 5, "MODE?", 5, get_mode);
    scpi_register_command(source, SCPI_CL_CHILD, "MODE", 4, "MODE", 4, set_mode);
    correction = scpi_register_command(source, SCPI_CL_CHILD, "CORRECTION", 10, "CORR", 4, NULL);
       correction_intensity = scpi_register_command(correction, SCPI_CL_CHILD, "INTENSITY", 9, "INT", 3, NULL);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "INTENSITY?", 10, "INT?", 4, get_intensity);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "FILTINTENSITY?", 14, "FILTINT?", 8, get_intensity_filtered);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "STATUS?", 7, "STAT?", 5, get_intensity_correction_status);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "STATUS?", 6, "STAT", 4, set_intensity_correction_status);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "FILTERTIME?", 11, "FILT?", 5, get_filterTime);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "FILTERTIME", 10, "FILT", 4, set_filterTime);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "VOLT2INTENSITY?", 15, "VOLT2INT?", 9, get_VoltToIntensity);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "VOLT2INTENSITY", 14, "VOLT2INT", 9, set_VoltToIntensity);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "INTENSITY2CURRENT?", 18, "INTENSITY2CUR?", 14, get_intensityToCurrent);
        scpi_register_command(correction_intensity, SCPI_CL_CHILD, "INTENSITY2CURRENT", 17, "INTENSITY2CUR", 13, set_intensityToCurrent);
       correction_temperature = scpi_register_command(correction, SCPI_CL_CHILD, "TEMPERATURE", 11, "TEMP", 4, NULL);
        scpi_register_command(correction_temperature, SCPI_CL_CHILD, "TEMP2CURRENT", 12, "TEMP2CUR", 8, set_temperature2current);
        scpi_register_command(correction_temperature, SCPI_CL_CHILD, "TEMP2CURRENT?", 13, "TEMP2CUR?", 9, get_temperature2current);
        scpi_register_command(correction_temperature, SCPI_CL_CHILD, "STATUS?", 7, "STAT?", 5, get_temperature_correction_status);
        scpi_register_command(correction_temperature, SCPI_CL_CHILD, "STATUS", 6, "STAT?", 4, set_temperature_correction_status);
      
}

scpi_error_t SCPI::get_temperature_correction_status(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);  
  if(DAC::temperatureCorrection)
    SerialUSB.println("Enabled");
  else SerialUSB.println("Disabled");
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_filterTime(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);  

  SerialUSB.println(configuration.intensityCorrection.filterTime);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_intensityToCurrent(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);  

  SerialUSB.println(configuration.intensityCorrection.intensity2current);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_VoltToIntensity(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);  
  SerialUSB.println(configuration.intensityCorrection.volt2intensity);
  return SCPI_SUCCESS;
}


scpi_error_t SCPI::get_intensity_correction_status(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);  
  if(DAC::intensityCorrection)
    SerialUSB.println("Enabled");
  else SerialUSB.println("Disabled");
  return SCPI_SUCCESS;
}


scpi_error_t SCPI::get_intensity(struct scpi_parser_context* context, struct scpi_token* command)
{
  Timer1.stop();
  scpi_free_tokens(command);  
  SerialUSB.println(A2DC::codeToIntensity(A2DC::readValue),4);
  Timer1.start();
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_temperature2current(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.temperatureCorrection.temperature2current,4);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_intensity_filtered(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(A2DC::_filteredIntensity,4);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::identify(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println("Lens driver");
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::measure_temperature(struct scpi_parser_context* context, struct scpi_token* command)
{
  if(LENS::temperature >0 & LENS::temperature<100)SerialUSB.println(LENS::temperature,4);  
  else
  {
    scpi_error error;
    error.id = -201;
    error.description = "Runtime error; No lens is connected; Once the lens is connected, the board needs to be restarted.";
    error.length = 97;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::reset_temperature(struct scpi_parser_context* context, struct scpi_token* command)
{
  TEC::init();
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_P(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.P);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_mode(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  if(DAC::mode==CONSTANT)SerialUSB.println("Constant");
  if(DAC::mode==ARBITRARY)SerialUSB.println("Arbitrary");
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_pid_minimum(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.imin);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_pid_maximum(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.imax);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_filterTime(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 1 && output_numeric.unit[0] == 's'))
  {
    configuration.intensityCorrection.filterTime=output_numeric.value;
    storeParameters(configuration);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_VoltToIntensity(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 3 && output_numeric.unit[0] == 'W' && output_numeric.unit[1] == '/' && output_numeric.unit[2] == 'V'))
  {
    configuration.intensityCorrection.volt2intensity=output_numeric.value;
    storeParameters(configuration);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_intensityToCurrent(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 4 && output_numeric.unit[0] == 'm' && output_numeric.unit[1] == 'A' && output_numeric.unit[2] == '/'  && output_numeric.unit[3] == 'W'))
  {
    configuration.intensityCorrection.intensity2current=output_numeric.value;
    storeParameters(configuration);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_pid_maximum(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 1 && output_numeric.unit[0] == 'A'))
  {
    configuration.TEC.imax=constrain(output_numeric.value,-2,2);
    storeParameters(configuration);
    TEC::pid.SetOutputLimits(configuration.TEC.imin,configuration.TEC.imax);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_temperature2current(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0)
  {
    configuration.temperatureCorrection.temperature2current=output_numeric.value;
    storeParameters(configuration);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_mode(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  
  if(args->length>0)
  {
      if(args->value[0]=='C')
      {
        TRIG::stopSequence();
        DAC::mode=CONSTANT;
      }
      else if(args->value[0]=='A')
      {
        if(DAC::len>0)
        {
          DAC::mode=ARBITRARY;
          if(TRIG::state)DAC::pos=DAC::len-1;
          else DAC::pos=0;
          DAC::write(DAC::codeToCurrent(DAC::getWordAt(DAC::pos)));
        }
        else
        {
          scpi_error error;
          error.id = -218;
          error.description = "Runtime error; No current sequence loaded";
          error.length = 41;    
          scpi_queue_error(&ctx, error);
          scpi_free_tokens(command);
          return SCPI_SUCCESS;
        }
      }    
       else
       {
        scpi_error error;
        error.id = -212;
        error.description = "Command error;Invalid mode";
        error.length = 26;    
        scpi_queue_error(&ctx, error);
        scpi_free_tokens(command);
        return SCPI_SUCCESS;
        }
  }
  else
  {
    scpi_error error;
    error.id = -212;
    error.description = "Command error;Invalid mode";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_temperature_correction_status(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  
  if(args->length>0)
  {
      String commandStr=String(args->value);
      if(commandStr.startsWith("ENA"))DAC::temperatureCorrection=true;
      if(commandStr.startsWith("DIS"))DAC::temperatureCorrection=false;
  }
  else
  {
    scpi_error error;
    error.id = -212;
    error.description = "Command error;Invalid mode";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_intensity_correction_status(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  
  if(args->length>0)
  {
      String commandStr=String(args->value);
      if(commandStr.startsWith("ENA"))DAC::intensityCorrection=true;
      if(commandStr.startsWith("DIS"))DAC::intensityCorrection=false;
  }
  else
  {
    scpi_error error;
    error.id = -212;
    error.description = "Command error;Invalid mode";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_frequency(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.DAC.frequency);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_frequency(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 2 && output_numeric.unit[0] == 'H' && output_numeric.unit[0] == 'Z'))
  {
    TRIG::stopSequence();
    DAC::mode=CONSTANT;
    DAC::clearArray();
    Timer0.setFrequency(output_numeric.value);
    configuration.DAC.frequency=Timer0.getFrequency();
    storeParameters(configuration);
    TEC::pid.SetOutputLimits(configuration.TEC.imin,configuration.TEC.imax);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}


scpi_error_t SCPI::set_pid_minimum(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 1 && output_numeric.unit[0] == 'A'))
  {
    
    configuration.TEC.imin=constrain(output_numeric.value,-2,2);
    storeParameters(configuration);
    TEC::pid.SetOutputLimits(configuration.TEC.imin,configuration.TEC.imax);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_P(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0 ||
  (output_numeric.length == 3 && output_numeric.unit[0] == 'A' && output_numeric.unit[1] == '/' && output_numeric.unit[2] == 'C'))
  {
    configuration.TEC.P=output_numeric.value;
    storeParameters(configuration);
    TEC::pid.SetTunings(configuration.TEC.P,configuration.TEC.I,configuration.TEC.D);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_currentMax(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.DAC.imax);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_currentMax(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -400, 400);
  if(output_numeric.length == 0 ||
    (output_numeric.length == 2 && output_numeric.unit[0] == 'M' && output_numeric.unit[1] == 'A'))
  {
    TRIG::stopSequence();
    DAC::mode=CONSTANT;
    DAC::clearArray();
    //At gain=2, the limits are 400 mA because the current source goes into saturation at higher values
    float value=(configuration.DAC.gain==1)?(constrain(output_numeric.value,-250,250)):(constrain(output_numeric.value,-400,400));
    configuration.DAC.imax=value;
    storeParameters(configuration);
    DAC::write(DAC::current);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_currentMin(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.DAC.imin);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_currentMin(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -400, 400);
  if(output_numeric.length == 0 ||
    (output_numeric.length == 2 && output_numeric.unit[0] == 'M' && output_numeric.unit[1] == 'A'))
  {
    TRIG::stopSequence();
    DAC::mode=CONSTANT;
    DAC::clearArray();
    //At gain=2, the limits are 400 mA because the current source goes into saturation at higher values
    float value=(configuration.DAC.gain==1)?(constrain(output_numeric.value,-250,250)):(constrain(output_numeric.value,-400,400));
    configuration.DAC.imin=value;
    storeParameters(configuration);
    DAC::write(DAC::current);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_I(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.I);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_I(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0||
  (output_numeric.length == 5 && output_numeric.unit[0] == 'A' && output_numeric.unit[1] == '/' && output_numeric.unit[2] == 'C' && output_numeric.unit[3] == '/' && output_numeric.unit[4] == 'S'))
  {
    configuration.TEC.I=output_numeric.value;
    storeParameters(configuration);
    TEC::pid.SetTunings(configuration.TEC.P,configuration.TEC.I,configuration.TEC.D);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_D(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.D);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_D(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0||
  (output_numeric.length == 5 && output_numeric.unit[0] == 'A' && output_numeric.unit[1] == '/' && output_numeric.unit[2] == 'C' && output_numeric.unit[3] == '*' && output_numeric.unit[4] == 'S'))
  {
    configuration.TEC.D=output_numeric.value;
    storeParameters(configuration);
    TEC::pid.SetTunings(configuration.TEC.P,configuration.TEC.I,configuration.TEC.D);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_setpoint(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(configuration.TEC.setpoint);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_setpoint(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0||
    (output_numeric.length == 1 && output_numeric.unit[0] == 'C'))
  {
    configuration.TEC.setpoint=output_numeric.value;
    storeParameters(configuration);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_output(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(TEC::output);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_current(struct scpi_parser_context* context, struct scpi_token* command)
{
  scpi_free_tokens(command);
  SerialUSB.println(DAC::current);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::set_current(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, -10, 10);
  if(output_numeric.length == 0||
    (output_numeric.length == 2 && output_numeric.unit[0] == 'M' && output_numeric.unit[1] == 'A'))
  {
    TRIG::stopSequence();
    DAC::mode=CONSTANT;
    DAC::write((float)output_numeric.value);
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::get_sequence(struct scpi_parser_context* context, struct scpi_token* command)
{
  if(DAC::len>0)
  {
    for(int i=0;i<DAC::len;i++)
    {
      SerialUSB.print(DAC::codeToCurrent(DAC::getWordAt(i)),3);
      SerialUSB.print(" ");
    }
    SerialUSB.println();
  }
  else
  {
    scpi_error error;
    error.id = -205;
    error.description = "Runtime error;No current sequence is loaded";
    error.length = 43;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}


scpi_error_t SCPI::set_sequence(struct scpi_parser_context* context, struct scpi_token* command)
{
  //Create an array of points and inititalise its values from Serial
  TRIG::stopSequence();
  DAC::mode=CONSTANT;
  struct scpi_token* args;
  struct scpi_numeric output_numeric;
  args = command;
  while(args != NULL && args->type == 0)args = args->next;
  output_numeric = scpi_parse_numeric(args->value, args->length, 0, 0, 30000);
  if(output_numeric.length == 0)
  {
    int N=output_numeric.value+0.1;
    DAC::clearArray();

    DAC::arr=new unsigned int[(N+1)/2*sizeof(unsigned int)];
    if(DAC::arr!=NULL)
    {
      DAC::len=N;
      for(int i=0;i<(N+1)/2;i++)
        DAC::arr[i]=0;
      for(int i=0;i<N;i++)
      {
          String valueStr=SerialUSB.readStringUntil('\n');
          float valueFloat=valueStr.toFloat();
          valueFloat=constrain(valueFloat,configuration.DAC.imin,configuration.DAC.imax);
          int value=DAC::currentToCode(valueFloat); 
          value=constrain(value,0,(1<<16)-1);
          DAC::arr[i/2]|=(value<<(16*(i%2)));
      }
    }   
    else
    {
        scpi_error error;
        error.id = -212;
        error.description = "Runtime error;Sequence is too large to fit in the memory";
        error.length = 56;    
        scpi_queue_error(&ctx, error);
        scpi_free_tokens(command);
        return SCPI_SUCCESS;
    }
  }
  else
  {
    scpi_error error;
    error.id = -200;
    error.description = "Command error;Invalid unit";
    error.length = 26;    
    scpi_queue_error(&ctx, error);
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
