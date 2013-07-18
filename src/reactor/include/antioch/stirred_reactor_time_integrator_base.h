//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// Antioch - A Gas Dynamics Thermochemistry Library
//
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

#ifndef ANTIOCH_STIRRED_REACTOR_TIME_INTEGRATOR_BASE_H
#define ANTIOCH_STIRRED_REACTOR_TIME_INTEGRATOR_BASE_H

// Antioch
#include "antioch/stirred_reactor_enum.h"
#include "antioch/stirred_reactor_base.h"

namespace Antioch
{
  // Foward declarations
  template<typename CoeffType, typename StateType>
  class BoostODEIntegrator;

  template<typename CoeffType=double, typename StateType=CoeffType>
  class StirredReactorTimeIntegratorBase
  {
  public:

    StirredReactorTimeIntegratorBase();

    virtual ~StirredReactorTimeIntegratorBase();

    //! Principal method for integrating ODE system.
    /*! Implemented in derived classes. We can't do virtual
        templated methods, so we settle for a runtime error
        if using the base class and not a derived class. 
        Returns number of time steps taken. */
    template<typename VectorStateType>
    unsigned int integrate( VectorStateType& x0,
                            CoeffType t0,
                            CoeffType t1,
                            CoeffType dt,
                            StirredReactorBase<CoeffType,StateType>& reactor,
                            StirredReactorObserver<CoeffType,VectorStateType>& observer );

  protected:

    TimeIntegratorType::TimeIntegratorType _integrator_type;

  };

  /* ---------------------- Constructor/Destructor ----------------------*/
  template<typename CoeffType, typename StateType>
  inline
  StirredReactorTimeIntegratorBase<CoeffType,StateType>::StirredReactorTimeIntegratorBase()
    : _integrator_type(TimeIntegratorType::INVALID)
  {
    return;
  }

  template<typename CoeffType, typename StateType>
  inline
  StirredReactorTimeIntegratorBase<CoeffType,StateType>::~StirredReactorTimeIntegratorBase()
  {
    return;
  }

  /* ------------------------- Inline Functions -------------------------*/
  template<typename CoeffType, typename StateType>
  template<typename VectorStateType>
  inline
  unsigned int StirredReactorTimeIntegratorBase<CoeffType,StateType>::integrate
  ( VectorStateType& x0,
    CoeffType t0,
    CoeffType t1,
    CoeffType dt,
    StirredReactorBase<CoeffType,StateType>& reactor,
    StirredReactorObserver<CoeffType,VectorStateType>& observer )
  {
    unsigned int n_steps = 0;

    switch( _integrator_type )
      {
      case( TimeIntegratorType::BOOST_ODE_INTEGRATOR ):
        {
          BoostODEIntegrator<CoeffType,StateType>* p = static_cast<BoostODEIntegrator<CoeffType,StateType>* >(this);
          n_steps = p->integrate(x0, t0, t1, dt, reactor, observer);
        }
        break;

      case( TimeIntegratorType::INVALID ):
        {
          std::cerr << "Error: Must use a valid, derived time integrator class." << std::endl;
          antioch_error();
        }
        break;

      // Wat?!
      default:
        {
          antioch_error();
        }

      } // switch( _integrator_type )

    return n_steps;
  }

} // end namespace Antioch

#endif // ANTIOCH_STIRRED_REACTOR_TIME_INTEGRATOR_BASE_H
