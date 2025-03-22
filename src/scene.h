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
 * Prints the structures of the scene to stdout
 *
 * @param scene  The scene whose structures are printed
 */
void print_scene_structures(const struct Scene* scene);

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
 * Adds a structure to a scene
 *
 * @param scene      The scene to which the structure is added
 * @param structure  The structure to add
 */
void add_structure(struct Scene* scene, const struct Structure* structure);

/**
 * Adds an antenna to a scene
 *
 * @param scene    The scene to which the antenna is added
 * @param antenna  The antenna to add
 */
void add_antenna(struct Scene* scene, const struct Antenna* antenna);

// Helper functions
// ---------------

/**
 * Creates a building structure
 *
 * @param id  The identifier of the building
 * @param x   The x coordinate
 * @param y   The y coordinate
 * @param w   The half width
 * @param h   The half height
 * @return    A new building structure
 */
struct Structure create_building(const char* id, int x, int y, int w, int h);

/**
 * Creates a house structure
 *
 * @param id  The identifier of the house
 * @param x   The x coordinate
 * @param y   The y coordinate
 * @param w   The half width
 * @param h   The half height
 * @return    A new house structure
 */
struct Structure create_house(const char* id, int x, int y, int w, int h);

/**
 * Gets the number of buildings in the scene
 *
 * @param scene  The scene
 * @return       The number of buildings
 */
unsigned int get_num_buildings(const struct Scene* scene);

/**
 * Gets the number of houses in the scene
 *
 * @param scene  The scene
 * @return       The number of houses
 */
unsigned int get_num_houses(const struct Scene* scene);

// Coverage quality
// ---------------------------------------------------

/**
 * Checks if a point is covered by any antenna in the scene.
 * 
 * @param x      The x-coordinate of the point
 * @param y      The y-coordinate of the point
 * @param scene  The scene containing the antennas
 * @return       true if the point is covered by at least one antenna
 */
bool is_point_covered(int x, int y, const struct Scene* scene);

/**
 * Counts the number of corners of a structure that are covered by antennas
 * 
 * @param structure  The structure to check coverage for
 * @param scene      The scene containing the antennas
 * @return           The number of corners covered (0-4)
 */
int count_structure_covered_corners(const struct Structure* structure, const struct Scene* scene);

/**
 * Gets a letter grade based on the number of covered corners
 * 
 * @param covered_corners  The number of corners that are covered (0-4)
 * @return                 A grade from 'A' (all corners covered) to 'E' (no coverage)
 */
char get_coverage_quality(int covered_corners);

#endif