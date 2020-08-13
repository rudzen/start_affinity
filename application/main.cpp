/*
 *  StartAffinity 1.4.0 (c) 2020 Rudy Alex Kohn
 *	rudzen@gmail.com
 *
 *  StartAffinity 1.3.1 (c) 2006 Adsci Engineering, LLC
 *	info@adsciengineering.com
 *
 *	This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <iostream>

#include "../cli/cli_parser.hpp"
#include "../src/start_affinity.hpp"

int main(const int argc, char *argv[])
{

  auto p = cli::make_parser(argc, argv, "start_affinity");

  return start_affinity::run(p.get());
}