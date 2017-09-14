#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
//#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"

#include "G4UIcommand.hh"

int main(int argc, char** argv)
{
  G4RunManager* runManager = new G4RunManager;

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  runManager -> SetUserInitialization(new DetectorConstruction);
  runManager -> SetUserInitialization(new PhysicsList);
  runManager -> SetUserInitialization(new ActionInitialization());

  runManager -> Initialize();
  
  // get pointer to UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI -> ApplyCommand("/control/execute init_vis.mac");
  ui -> SessionStart();
  
  delete ui;

  // TERMINATE job
  delete runManager;
  delete visManager; 
  
  // We will output the table of materials that were used when we end the program
  // We could also place this within DetectorConstruction and have it output when
  // we start the program
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  return 0;
}
