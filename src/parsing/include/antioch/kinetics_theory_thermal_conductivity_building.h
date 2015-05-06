//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// Antioch - A Gas Dynamics Thermochemistry Library
//
// Copyright (C) 2014 Paul T. Bauman, Benjamin S. Kirk, Sylvain Plessis,
//                    Roy H. Stonger
// Copyright (C) 2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-

#ifndef ANTIOCH_KINETICS_THEORY_THERMAL_CONDUCTIVITY_BUILDING_H
#define ANTIOCH_KINETICS_THEORY_THERMAL_CONDUCTIVITY_BUILDING_H

// Antioch
#include "antioch/kinetics_theory_thermal_conductivity.h"
#include "antioch/physical_set.h"
#include "antioch/mixture_conductivity.h"

// C++
#include <iostream>
#include <vector>


namespace Antioch
{

  template <typename ThermoEvaluator, typename NumericType>
  class TransportMixture;


  template<class ThermoTC, class ThermoTran, class NumericType>
  void build_kinetics_theory_thermal_conductivity( PhysicalSet<KineticsTheoryThermalConductivity<ThermoTC,NumericType> , TransportMixture<ThermoTran,NumericType> >& k);

// ----------------------------------------- //

  template<class ThermoTC, class ThermoTran,class NumericType>
  void build_kinetics_theory_thermal_conductivity( PhysicalSet<KineticsTheoryThermalConductivity<ThermoTC,NumericType>, TransportMixture<ThermoTran,NumericType> >& k)
  {
       for(unsigned int s = 0; s < k.mixture().n_species(); s++)
       {
           Initializer<KineticsTheoryThermalConductivity<ThermoTC,NumericType>, kinetics_theory_thermal_conductivity_tag >
             init(k.mixture().thermo().micro_thermo(),
                  k.mixture().transport_species()[s]->rotational_relaxation(),
                  k.mixture().transport_species()[s]->LJ_depth());
           k.add_model(k.mixture().species_inverse_name_map().at(s),init);
       }
  }

  template<class ThermoTC, class ThermoTran,class NumericType>
  void build_kinetics_theory_thermal_conductivity(MixtureConductivity<KineticsTheoryThermalConductivity<ThermoTC,NumericType>,ThermoTran,ThermoTC,NumericType>& k )
  {
    for(unsigned int s = 0; s < k.mixture().n_species(); s++)
       {
         std::vector<NumericType> coeffs(2);
         coeffs[0] = k.mixture().transport_species()[s]->rotational_relaxation();
         coeffs[1] = k.mixture().transport_species()[s]->LJ_depth();
         k.add(s,coeffs,k.mixture().thermo().micro_thermo());
       }
  }

} // end namespace Antioch

#endif // ANTIOCH_KINETICS_THEORY_THERMAL_CONDUCTIVITY_BUILDING_H
