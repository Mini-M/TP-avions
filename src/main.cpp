#include "Avion.h"
#include "AvionAmi.h"
#include "AvionEnnemi.h"
#include "GeneralCallback.h"

using namespace std;

int main()

{
    // Initialisation avions (pas besoin des symboles, le symmbole est inclus dans le constructeur AvionAmi et Avion Ennemi)
    Avion* avion1 = new AvionAmi(0,0,5,0,1,0,1);  
    Avion* avion2 = new AvionAmi(1,0,8,0,1,0,1);
    Avion* avion3 = new AvionEnnemi(2,13,5,13,-1,0,-1);
    Avion* avion4 = new AvionEnnemi(3,13,8,13,-1,0,-1);


    // Initialisation OSG <3  <3
    
/* OBJECTS CREATION */

	//Creating the viewer	
	osgViewer::Viewer viewer ;

	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);

/* SPACESHIPS	*/

	//Loading the SPACESHIPS nodes
	osg::ref_ptr<osg::Node> xWing (osgDB::readNodeFile("/home/user/Documents/MEDEV/TP-avions/y-wing/y-wing.3ds"));
	osg::ref_ptr<osg::Node> tFighter (osgDB::readNodeFile("/home/user/Documents/MEDEV/TP-avions/E-TIE-I/E-TIE-I.3ds"));

/* Scale Matrix	*/

	// Create transformation node 
	osg::ref_ptr<osg::MatrixTransform> matXWing (new osg::MatrixTransform);
	osg::ref_ptr<osg::MatrixTransform> matTFighter (new osg::MatrixTransform);

	// Scale matrix
	osg::Matrix matrixXWing;
	matrixXWing.makeScale(osg::Vec3f(0.001,0.001,0.001));

	osg::Matrix matrixTFighter;
	matrixTFighter.makeScale(osg::Vec3f(0.003,0.003,0.003));

	//Set transformation node parameters
	matXWing->addChild(xWing.get());
	matXWing->setMatrix(matrixXWing);

	matTFighter->addChild(tFighter.get());
	matTFighter->setMatrix(matrixTFighter);

/* POSITIONS */

	osg::ref_ptr<osg::PositionAttitudeTransform> patXWing (new osg::PositionAttitudeTransform); 
	//osg::Vec3f posXWing(0,50,0);		//Set the position 
	//patXWing->setPosition(posXWing);
	patXWing->addChild(matXWing.get());

	osg::Quat qR;                            
	qR.makeRotate(-4.14,osg::Vec3(0,0,1));  //Set the direction of the "Gentils" Spaceship
	patXWing->setAttitude(qR);

	osg::ref_ptr<osg::PositionAttitudeTransform> patTFigther (new osg::PositionAttitudeTransform); 
	osg::Vec3f posTFighter(-0.3,-0.15,0.1);     //Set the position
	patTFigther->setPosition(posTFighter);
	patTFigther->addChild(matTFighter.get()); 

	qR.makeRotate(1.57,osg::Vec3(0,0,1));  //Set the direction of the "Mechants" Spaceship
	patTFigther->setAttitude(qR);

	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 (new osg::PositionAttitudeTransform);
	pat1->addChild(patXWing.get());
	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 (new osg::PositionAttitudeTransform);
	pat2->addChild(patXWing.get());
	osg::ref_ptr<osg::PositionAttitudeTransform> pat3 (new osg::PositionAttitudeTransform);
	pat3->addChild(patTFigther.get());
	osg::ref_ptr<osg::PositionAttitudeTransform> pat4 (new osg::PositionAttitudeTransform);
	pat4->addChild(patTFigther.get());


/* SCENE GRAPH*/

	// Add the geode to the scene graph root (Group)
	root->addChild(pat1.get());
	root->addChild(pat2.get());
	root->addChild(pat3.get());
	root->addChild(pat4.get());

	// Set the scene data
	viewer.setSceneData( root.get() ); 

/* KEYBOARD INPUT */
	
 	//Stats Event Handler s key
	viewer.addEventHandler(new osgViewer::StatsHandler);

	//Windows size handler
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	
	// add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );

	
/* START VIEWER */
	osg::ref_ptr<GeneralCallback> generalCallback = new GeneralCallback();
	generalCallback->patAvions.push_back(pat1);
	generalCallback->patAvions.push_back(pat2);
	generalCallback->patAvions.push_back(pat3);
	generalCallback->patAvions.push_back(pat4);
	root->addUpdateCallback(generalCallback);

	//The viewer.run() method starts the threads and the traversals.
	viewer.getCamera()->setClearColor(osg::Vec4(0.0f,0.0f,0.2f,0.0f));

	cout << "*** Begin ***" << endl;
	return (viewer.run());
}
