#ifndef SCPI_H
#define SCPI_H

#include"scpiparser.h"
#include"utils.h"
struct SCPI
{
   static struct scpi_parser_context ctx;
   static void init(void);
   static struct scpi_command* temperature;
   static struct scpi_command* pid;
   static struct scpi_command* source;
   static struct scpi_command* arbitrary;
   static struct scpi_command* current_limit;
   static struct scpi_command* pid_limit;
   static struct scpi_command* correction;
   static struct scpi_command* correction_intensity;
   static struct scpi_command* correction_temperature;


   static scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t measure_temperature(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_P(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_P(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_I(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_I(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_D(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_D(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_setpoint(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_pid_minimum(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_pid_maximum(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_pid_minimum(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_pid_maximum(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_setpoint(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_output(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t reset_temperature(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_current(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_current(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_currentMax(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_currentMax(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_currentMin(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_currentMin(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_sequence(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_sequence(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_frequency(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_frequency(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_mode(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_mode(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_filterTime(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_filterTime(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_VoltToIntensity(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_VoltToIntensity(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_intensity(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_intensity_filtered(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_temperature2current(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_intensityToCurrent(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_intensityToCurrent(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_temperature2current(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_temperature_correction_status(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_temperature_correction_status(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t get_intensity_correction_status(struct scpi_parser_context* context, struct scpi_token* command);
   static scpi_error_t set_intensity_correction_status(struct scpi_parser_context* context, struct scpi_token* command);

};
struct scpi_parser_context SCPI::ctx;
struct scpi_command* SCPI::temperature;
struct scpi_command* SCPI::pid;
struct scpi_command* SCPI::source;
struct scpi_command* SCPI::arbitrary;
struct scpi_command* SCPI::current_limit;
struct scpi_command* SCPI::pid_limit;
struct scpi_command* SCPI::correction;
struct scpi_command* SCPI::correction_intensity;
struct scpi_command* SCPI::correction_temperature;

#endif
