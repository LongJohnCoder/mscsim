/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef FDM_MASS_H
#define FDM_MASS_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <fdm/fdm_Base.h>

#include <fdm/utils/fdm_Matrix3x3.h>
#include <fdm/utils/fdm_Matrix6x6.h>
#include <fdm/utils/fdm_Vector3.h>

#include <fdm/xml/fdm_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

class Aircraft; ///< aircraft class forward declaration

/**
 * @brief Mass, inertia, balance and gravity class.
 *
 * <p>Input data reference is created for each variable mass component. Name of
 * this data reference is "input/mass/variable_mass_component_name".</p>
 *
 * <h5>XML configuration file format:</h5>
 * @code
 * <mass>
 *   <empty_mass> { [kg] empty aircraft mass } </empty_mass>
 *   <inertia_tensor>
 *     { [kg*m^2] Ixx } { [kg*m^2] Ixy } { [kg*m^2] Ixz }
 *     { [kg*m^2] Iyx } { [kg*m^2] Iyy } { [kg*m^2] Iyz }
 *     { [kg*m^2] Izx } { [kg*m^2] Izy } { [kg*m^2] Izz }
 *   </inertia_tensor>
 *   <center_of_mass> { [m] x-coordinate } { [m] y-coordinate } { [m] z-coordinate } </center_of_mass>
 *   <variable_mass input="{ variable mass input name }">
 *     <mass_max> { [kg] maximum mass } </mass_max>
 *     <coordinates> { [m] x-coordinate } { [m] y-coordinate } { [m] z-coordinate } </coordinates>
 *   </variable_mass>
 *   ... { more variable masses }
 * </mass>
 * @endcode
 *
 * @see Taylor J.: Classical Mechanics, 2005, p.411
 * @see Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.40, [in Polish]
 * @see Narkiewicz J,: Tiltrotor Modelling for Simulation in Various Flight Conditions, 2006
 * @see https://en.wikipedia.org/wiki/Parallel_axis_theorem
 */
class FDMEXPORT Mass : public Base
{
public:

    /** Variable mass component data. */
    struct VarMass
    {
        const double *input;    ///< [kg] mass input
        double mass;            ///< [kg] mass
        double mass_max;        ///< [kg] maximum mass
        Vector3 r_bas;          ///< [m] position expressed in BAS
    };

    typedef std::map< std::string, VarMass > Masses;

    /** Constructor. */
    Mass( const Aircraft* aircraft );

    /** Destructor. */
    virtual ~Mass();

    /** Initializes mass. */
    virtual void init();

    /**
     * Reads data.
     * @param dataNode XML node
     */
    virtual void readData( XmlNode &dataNode );

    /** Computes force and moment. */
    virtual void computeForceAndMoment();

    /** Updates mass. */
    virtual void update();

    inline const Vector3& getFor_BAS() const { return m_for_bas; }
    inline const Vector3& getMom_BAS() const { return m_mom_bas; }

    /**
     * Returns total mass.
     * @return [kg] total mass
     */
    inline double getMass() const { return m_mass_t; }

    /**
     * Returns inertia matrix.
     * @return inertia matrix
     */
    virtual Matrix6x6 getInertiaMatrix() const;

    /**
     * Returns inertia tensor for total mass.
     * @return [kg*m^2] inertia tensor
     */
    inline Matrix3x3 getInertiaTensor() const { return m_it_t_bas; }

    /**
     * Returns first moment of mass (total).
     * @return [kg*m] first moment of mass
     */
    Vector3 inline getFirstMomentOfMass() const { return m_st_t_bas; }

protected:

    const Aircraft *m_aircraft; ///< aircraft model main object

    Vector3 m_for_bas;          ///< [N] total force vector expressed in BAS
    Vector3 m_mom_bas;          ///< [N*m] total moment vector expressed in BAS

    Masses m_masses;            ///< variable masses array

    double m_mass_e;            ///< [kg] empty aircraft mass
    double m_mass_t;            ///< [kg] total aircraft mass

    Vector3 m_cm_e_bas;         ///< [m] center of mass (empty) expressed in BAS
    Vector3 m_cm_t_bas;         ///< [m] center of mass (total) expressed in BAS

    Vector3 m_st_t_bas;         ///< [kg*m] first mass moment (total) vector expressed in BAS

    Matrix3x3 m_it_e_bas;       ///< [kg*m^2] inertia tensor (empty)
    Matrix3x3 m_it_t_bas;       ///< [kg*m^2] inertia tensor (total)

    /**
     * Adds variable mass to the total aircraft mass.
     * @param variableMass variable mass component
     */
    virtual void addVariableMass( const VarMass &varMass );

    /**
     * Returns variable mass by name.
     * @param name variable mass name
     * @return channel
     */
    virtual VarMass* getVariableMassByName( const std::string &name );

private:

    /** Using this constructor is forbidden. */
    Mass( const Mass & ) {}
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FDM_MASS_H