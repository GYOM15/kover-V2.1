#ifndef SCENE_H_
#define SCENE_H_

#include <stdbool.h>
#include "validation.h"

// Constants
// ---------

// The maximum length of an identifier
#define MAX_LENGTH_ID 10
// The maximum number of buildings in a scene
#define NUM_MAX_BUILDINGS 100
// The maximum number of houses in a scene
#define NUM_MAX_HOUSES 100
// The maximum number of antennas in a scene
#define NUM_MAX_ANTENNAS 100

// Types
// -----

// Structure type enum
enum StructureType {
  BUILDING,
  HOUSE
};

// A unified structure for buildings and houses
struct Structure {
  // The identifier of the structure
  char id[MAX_LENGTH_ID + 1];
  // Type of structure (building or house)
  enum StructureType type;
  // Coordinates
  int x;
  int y;
  // The half width (half length in x direction)
  int w;
  // The half height (half length in y direction)
  int h;
};

// An antenna
struct Antenna {
  // The identifier of the antenna
  char id[MAX_LENGTH_ID + 1];
  // The x coordinate of the antenna
  int x;
  // The y coordinate of the antenna
  int y;
  // The radius of the antenna
  int r;
};

// A scene
struct Scene {
  // The number of structures in the scene
  unsigned int num_structures;
  // The structures of the scene
  struct Structure structures[NUM_MAX_BUILDINGS + NUM_MAX_HOUSES];
  
  // The number of antennas in the scene
  unsigned int num_antennas;
  // The antennas of the scene
  struct Antenna antennas[NUM_MAX_ANTENNAS];
};

// Construction
// ------------

/**
 * Initializes an empty scene
 *
 * @param scene  The scene to initialize
 */
void initialize_empty_scene(struct Scene* scene);

/**
 * Loads a scene from the standard input
 *
 * @param scene  The resulting scene
 */
void load_scene_from_stdin(struct Scene* scene);

// Validation
// ----------

/**
 * Checks if a scene is valid
 *
 * If the scene is invalid, an error is printed on stdout and the program exits
 * with 1.
 *
 * @param scene  The scene to validate
 */
void validate_scene(const struct Scene* scene);

/**
 * Checks if there are any overlapping structures in the scene
 *
 * @param scene  The scene to validate
 * @param error  Structure to store error information
 * @return       true if an overlap is found, false otherwise
 */
bool validate_structures_overlaps(const struct Scene* scene, struct ValidationError* error);

/**
 * Checks if there are antennas with the same position
 *
 * @param scene  The scene to validate
 * @param error  Structure to store error information
 * @return       true if same position antennas are found, false otherwise
 */
bool validate_antennas(const struct Scene* scene, struct ValidationError* error);

/**
 * Indicates if two structures are overlapping
 *
 * Two structures are overlapping if their intersection has a strictly positive
 * area.
 *
 * @param structure1  The first structure
 * @param structure2  The second structure
 * @return           true if and only if they overlap
 */
bool are_structures_overlapping(const struct Structure* structure1,
                               const struct Structure* structure2);

/**
* Indicates if two antennas have the same position
*
* @param antenna1  The first antenna
* @param antenna2  The second antenna
* @return         true if and only if they have the same position
*/
bool have_antennas_same_position(const struct Antenna* antenna1,
                                const struct Antenna* antenna2);

// Accessors
// ---------

/**
 * Indicates if a scene is empty
 *
 * @param scene  The scene to check
 * @return       true if and only if the given scene is empty
 */
bool scene_is_empty(const struct Scene* scene);

/**
 * Prints a summary of the scene on stdout
 *
 * @param scene  The scene to print
 */
void print_scene_summary(const struct Scene* scene);

/**
 * Prints the antenna of the scene to stdout
 *
 * @param scene  The scene whose antennas are printed
 */
void print_scene_antennas(const struct Scene* scene);

/**
 * Prints the bounding box of the scene to stdout
 *
 * @param scene  The scene whose bounding box is printed
 */
void print_scene_bounding_box(const struct Scene* scene);

// Modifiers
// ---------

/**
 * Adds an antenna to a scene
 *
 * @param scene    The scene to which the antenna is added
 * @param antenna  The antenna to add
 */
void add_antenna(struct Scene* scene, const struct Antenna* antenna);

// Helper functions
// ---------------

#endif