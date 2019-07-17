#define BOOST_TEST_MODULE test_Polynomial

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <BigNumbers/BigNumbers.h>
#include <ThresholdSignatures/Polynomial.h>

#include <string>
#include <iostream>


BOOST_AUTO_TEST_SUITE( test_suite_Polynomial )


/* Create a new polynomial using the string constructor
 *   Check the degree
 *   Evaluate the point for x=0,1
 *   Check the coefficients
 */
BOOST_AUTO_TEST_CASE( test_polynomial_degree1 )
{
    // 3 + 2x 
    std::vector< std::string>  strCoefficients { "3",  "2" } ;     
    Polynomial poly ( strCoefficients, GenerateZero( ) ) ;

    long degree = poly.getDegree( ) ;
    BOOST_CHECK_EQUAL ( degree, strCoefficients.size() - 1 ) ;

    BigNumber fx_0, fx_1, eval_at_0, eval_at_1 ;
    fx_0.FromDec( "0" ) ;
    fx_1.FromDec( "1" ) ;
    eval_at_0 = poly( fx_0 ) ;
    eval_at_1 = poly( fx_1 ) ;
    
    BOOST_TEST  ( eval_at_0.ToDec() == "3"  ) ;
    BOOST_TEST  ( eval_at_1.ToDec() == "5"  ) ;

    //std::cout << "Sanity check:" << std::endl ;
    //std::cout << "eval_at_0 = " << eval_at_0.ToDec( ) << std::endl ;
    //std::cout << "eval_at_1 = " << eval_at_1.ToDec( ) << std::endl ;

    std::ostringstream ss ;
    ss << poly ;
    BOOST_TEST ( ss.str( ) == "modulo = 0;	polynomial = 3 + 2x" ) ;
}

/* Create a new polynomial using the vector constr
 *   Evaluate the point for x=0,1,2
 *   Check the coefficients
 */
BOOST_AUTO_TEST_CASE( test_polynomial_degree2 )
{
     // 1 + 2x + 3x^2 
    std::vector< std::string >  strCoefficients { "1",  "2", "3" } ;     
    std::vector< BigNumber >    bnCoefficients ;

    for ( auto & element : strCoefficients )
    {
        BigNumber big ;
	    big.FromDec( element ) ;
        bnCoefficients.push_back( std::move( big ) ) ;
    }

    Polynomial poly ( bnCoefficients, GenerateZero( ) ) ;

    BigNumber fx_0, fx_1, fx_2, eval_at_0, eval_at_1, eval_at_2;
    fx_0.FromDec( "0" ) ;
    fx_1.FromDec( "1" ) ;
    fx_2.FromDec( "2" ) ;

    eval_at_0 = poly( fx_0 ) ;
    eval_at_1 = poly( fx_1 ) ;
    eval_at_2 = poly( fx_2 ) ;

    BOOST_TEST  ( eval_at_0.ToDec( ) == "1" ) ;
    BOOST_TEST  ( eval_at_1.ToDec( ) == "6" ) ;
    BOOST_TEST  ( eval_at_2.ToDec( ) == "17" ) ;

    std::ostringstream ss ;
    ss << poly ;
    BOOST_TEST ( ss.str( ) == "modulo = 0;	polynomial = 1 + 2x + 3x^2" ) ;
}

/* Create a new polynomial using the string constructor
 *   Check the mod function
 *   Check the [] operator
 *   Check the f(x) for a vector
 */
BOOST_AUTO_TEST_CASE( test_polynomial_degree2_mod )
{
    // 6 + 7x + 8x^2  [mod 5]
    std::vector< std::string>  strCoefficients { "6",  "7", "8" } ;     
    BigNumber modulo ;
    modulo.FromDec( "5" ) ;

    Polynomial poly ( strCoefficients, modulo ) ;

    BigNumber array_0, array_1, array_2 ;
    array_0.FromDec( "1" ) ;
    array_1.FromDec( "2" ) ;
    array_2.FromDec( "3" ) ;

    BOOST_CHECK  ( ( poly[ 0 ] ) ==  array_0 ) ;
    BOOST_CHECK  ( ( poly[ 1 ] ) ==  array_1 ) ;
    BOOST_CHECK  ( ( poly[ 2 ] ) ==  array_2 ) ;


    BigNumber fx_0, fx_1, fx_2, eval_at_0, eval_at_1, eval_at_2;
    fx_0.FromDec( "0" ) ;
    fx_1.FromDec( "1" ) ;
    fx_2.FromDec( "2" ) ;

    eval_at_0 = poly( fx_0 ) ;
    eval_at_1 = poly( fx_1 ) ;
    eval_at_2 = poly( fx_2 ) ;

    BOOST_TEST  ( eval_at_0.ToDec( ) == "1" ) ;
    BOOST_TEST  ( eval_at_1.ToDec( ) == "1" ) ;
    BOOST_TEST  ( eval_at_2.ToDec( ) == "2" ) ;

   
    std::ostringstream ss ;
    ss << poly ;
    BOOST_TEST ( ss.str( ) == "modulo = 5;	polynomial = 1 + 2x + 3x^2" ) ;
}

/* Create a new polynomial using the vector constructor
 *   Check the mod function
 *   Check the f(x) for x = 0,1,2
 */
BOOST_AUTO_TEST_CASE( test_polynomial_degree2_mod2 )
{
    // 16 + 9x^2  [mod 5]
    std::vector< std::string>  strCoefficients { "16",  "0", "9" } ;     
    BigNumber modulo ;
    modulo.FromDec( "5" ) ;

    std::vector< BigNumber >    bnCoefficients ;

    for ( auto & element : strCoefficients )
    {
        BigNumber big ;
	    big.FromDec( element ) ;
        bnCoefficients.push_back( std::move( big ) ) ;
    }

    Polynomial poly ( bnCoefficients, modulo ) ;


    BigNumber array_0, array_1, array_2;

    array_0.FromDec( "1" ) ;
    array_1.FromDec( "0" ) ;
    array_2.FromDec( "4" ) ;

    BOOST_CHECK  ( ( poly[ 0 ] ) ==  array_0 ) ;
    BOOST_CHECK  ( ( poly[ 1 ] ) ==  array_1 ) ;
    BOOST_CHECK  ( ( poly[ 2 ] ) ==  array_2 ) ;

    BigNumber fx_0, fx_1, fx_2, eval_at_0, eval_at_1, eval_at_2;
    fx_0.FromDec( "0" ) ;
    fx_1.FromDec( "1" ) ;
    fx_2.FromDec( "2" ) ;

    eval_at_0 = poly( fx_0 ) ;
    eval_at_1 = poly( fx_1 ) ;
    eval_at_2 = poly( fx_2 ) ;

    BOOST_TEST  ( eval_at_0.ToDec( ) == "1" ) ;
    BOOST_TEST  ( eval_at_1.ToDec( ) == "0" ) ;
    BOOST_TEST  ( eval_at_2.ToDec( ) == "2" ) ;

    std::ostringstream ss ;
    ss << poly ;
    BOOST_TEST ( ss.str( ) == "modulo = 5;	polynomial = 1 + 0x + 4x^2" ) ;    
}



BOOST_AUTO_TEST_SUITE_END( ) ;

/* 
    <todo>
    What elses do we need to test?
    - small polynomial with random inputs
    - small polynomial with big number
    - Assignments ?
 */
