/*
  OMPi OpenMP Compiler
  == Copyright since 2001 the OMPi Team
  == Dept. of Computer Science & Engineering, University of Ioannina

  This file is part of OMPi.

  OMPi is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  OMPi is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OMPi; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/* ast_free.h */

#ifndef __AST_FREE_H__
#define __AST_FREE_H__

#include "ast.h"

#define ast_free(tree) ast_stmt_free(tree)

extern void ast_stmt_free(aststmt t);
extern void ast_expr_free(astexpr t);
extern void ast_decl_free(astdecl t);
extern void ast_spec_free(astspec t);
extern void ast_ompcon_free(ompcon t);
extern void ast_ompclause_free(ompclause t);
extern void ast_ompdir_free(ompdir t);
extern void ast_ompxli_free(ompxli xl);

/* OMPi-extensions
 */
extern void ast_oxclause_free(oxclause t);
extern void ast_oxdir_free(oxdir t);
extern void ast_oxcon_free(oxcon t);

#endif

