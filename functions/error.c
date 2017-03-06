/*
** error.c for error in /home/nathan.michel/Cours/Semestre2/PSU/PSU_2016_navy
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Mon Jan 30 16:42:22 2017 Nathan MICHEL
** Last update Fri Feb  3 15:08:46 2017 Timothée Couble
*/

#include "../include/my.h"

int	my_puterror(char *str)
{
  write(2, str, my_strlen(str));
  return (84);
}
