#include <iostream>

#include <Eigen/Core>

#include <cvt/math/LevenbergMarquard.h>
#include <cvt/math/CostFunction.h>
#include <cvt/math/Math.h>
#include <cvt/util/RNG.h>
#include <cvt/util/Time.h>

#include <cvt/vision/CamModel.h>
#include <cvt/vision/PointCorrespondences3d2d.h>

using namespace cvt;

void generateData( PointCorrespondences3d2d<double> & data, size_t n )
{
	RNG rng( time( NULL ) );
	double sigma = 0.01;
	
	Eigen::Matrix<double, 3, 1> p3d;
	Eigen::Matrix<double, 2, 1> p2d;
	
	while ( n-- ) {
		p3d[ 0 ] = rng.uniform( -100.0, 100.0 );
		p3d[ 1 ] = rng.uniform( -100.0, 100.0 );
		p3d[ 2 ] = rng.uniform( -100.0, 100.0 );	
		
		data.pose().project( p2d, data.camModel(), p3d );
				
		// add some noise
		p2d[ 0 ] += rng.gaussian( sigma ); 
		p2d[ 1 ] += rng.gaussian( sigma );
		
		data.add( p3d, p2d );
	}
}

int main()
{
	size_t numPoints = 300;
	
	Eigen::Matrix<double, 3, 3> K = Eigen::Matrix<double, 3, 3>::Identity();
	Eigen::Matrix<double, 4, 4> T = Eigen::Matrix<double, 4, 4>::Identity();
	
	K( 0, 0 ) = 600; K( 0, 2 ) = 399.5;
	K( 1, 1 ) = 600; K( 1, 2 ) = 299.5;
	
	CamModel<double> cam( K, T );
	PointCorrespondences3d2d<double> model( cam );
	
	Eigen::Matrix<double, 6, 1> poseVec;
	poseVec[ 0 ] = Math::deg2Rad( 10.0 ); 
	poseVec[ 1 ] = Math::deg2Rad( 40.0 ); 
	poseVec[ 2 ] = Math::deg2Rad( 90.0 );
	poseVec[ 3 ] = 100; 
	poseVec[ 4 ] = 200; 
	poseVec[ 5 ] = 300;
	model.apply( poseVec );
	
	std::cout << "Ground Truth:\n" << model.pose().transformation() << std::endl;
	
	// generate random points
	generateData( model, numPoints );		
	
	// perturbe the current pose, to use it as initial estimate
	poseVec = Eigen::Matrix<double, 6, 1>::Zero();
	poseVec[ 0 ] += Math::deg2Rad( 0.5 );
	poseVec[ 1 ] -= Math::deg2Rad( 0.1 );
	poseVec[ 2 ] += Math::deg2Rad( 0.0 );
	poseVec[ 3 ] -= 10;
	poseVec[ 4 ] -= 10;
	poseVec[ 5 ] += 30;
	model.apply( poseVec );
	std::cout << "Initial Transformation: \n" << model.pose().transformation() << std::endl; 

	TerminationCriteria<double> termCriteria;
	termCriteria.setCostThreshold( 0.00001 );
	termCriteria.setMaxIterations( 100 );
	
	LevenbergMarquard<double> lm( termCriteria );
	CostFunction<double, Eigen::Matrix<double, 2, 1> > costFunc;
	
	Time timer;
	lm.optimize( model, costFunc, ( TERM_COSTS_THRESH | TERM_MAX_ITER ) );

	std::cout << "Elapsed time: " << timer.elapsedMilliSeconds() << "ms" << std::endl;
	std::cout << "Optimized:\n" << model.pose().transformation() << std::endl;
	std::cout << "Iterations: " << lm.iterations() << std::endl;
	std::cout << "Final Costs: " << lm.costs() << std::endl;
	
	return 0;
}