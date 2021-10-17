//
//  file.hpp
//  acid_posix
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 20:57 BRT
//  <3ThomasBorregaardSorensen!!
//
#pragma once


int posix_file_lock(int iFileDescriptor);
int posix_file_unlock(int iFileDescriptor);
int posix_close(int iFileDescriptor);


