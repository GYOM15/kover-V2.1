#include "scene.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"

// Private constants, types and functions
// ======================================

// Constants
// ---------

// The maximum length of a line in a scene stream
#define MAX_LENGTH 50
// The maximum number of tokens in a line
#define MAX_NUM_TOKENS 6
// The maximum length of a token in a line
#define MAX_TOKEN_LENGTH 10

// Types
// -----

// A parsed line
struct ParsedLine {
  // The number of parsed token
  unsigned int num_tokens;
  // The tokens
  char tokens[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];
  // The number of the line
  int line_number;
};

// Validation
// ----------

/**
 * Indicates if two intervals are overlapping
 *
 * @param a1  The start of the first interval
 * @param b1  The end of the first interval
 * @param a2  The start of the second interval
 * @param b2  The end of the second interval
 */
bool are_intervals_overlapping(int a1, int b1, int a2, int b2) {
  return (a1 <= a2 && a2 < b1 && b1 <= b2) ||
         (a2 <= a1 && a1 < b2 && b2 <= b1);
}

// Loading
// -------

/**
 * Indicates if the line is a valid "begin scene" line
 *
 * @param line  The line to check
 * @return      true if and only if the line is valid
 */
bool is_begin_scene_line(const char* line) {
  return strcmp(line, "begin scene") == 0;
}

/**
 * Indicates if the line is a valid "end scene" line
 *
 * @param line  The line to check
 * @return      true if and only if the line is valid
 */
bool is_end_scene_line(const char* line) {
  return strcmp(line, "end scene") == 0;
}

/**
 * Parses a line
 *
 * @param line         The line to parse
 * @param parsed_line  The resulting parsed line
 * @param line_number  The number of the line
 */
void parse_line(const char* line,
                struct ParsedLine* parsed_line,
                int line_number) {
  char line_copy[MAX_LENGTH + 1];
  strncpy(line_copy, line, MAX_LENGTH);
  char *token = strtok(line_copy, " ");
  int t = 0;
  while (token != NULL) {
    strncpy(parsed_line->tokens[t], token, MAX_TOKEN_LENGTH);
    ++t;
    token = strtok(NULL, " ");
  }
  parsed_line->num_tokens = t;
  parsed_line->line_number = line_number;
}

/**
 * Loads a building from a parsed line
 *
 * @param parsed_line  The parsed line
 * @param scene        The scene in which the building is loaded
 * @return             true if and only if the loading was successful
 */
bool load_building_from_parsed_line(const struct ParsedLine* parsed_line,
                                    struct Scene* scene) {
  if (strcmp(parsed_line->tokens[0], "building") != 0)
    return false;
  if (parsed_line->num_tokens != 6)
    report_error_line_wrong_arguments_number("building",
                                             parsed_line->line_number);
  if (!is_valid_id(parsed_line->tokens[1]))
      report_error_invalid_identifier(parsed_line->tokens[1],
                                      parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[2]))
      report_error_invalid_int(parsed_line->tokens[2],
                               parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[3]))
      report_error_invalid_int(parsed_line->tokens[3],
                               parsed_line->line_number);
  if (!is_valid_positive_integer(parsed_line->tokens[4]))
      report_error_invalid_positive_int(parsed_line->tokens[4],
                                        parsed_line->line_number);
  if (!is_valid_positive_integer(parsed_line->tokens[5]))
      report_error_invalid_positive_int(parsed_line->tokens[5],
                                        parsed_line->line_number);
  
  struct Structure building = create_building(
    parsed_line->tokens[1],
    atoi(parsed_line->tokens[2]),
    atoi(parsed_line->tokens[3]),
    atoi(parsed_line->tokens[4]),
    atoi(parsed_line->tokens[5])
  );
  
  add_structure(scene, &building);
  return true;
}

/**
 * Loads a house from a parsed line
 *
 * @param parsed_line  The parsed line
 * @param scene        The scene in which the house is loaded
 * @return             true if and only if the loading was successful
 */
bool load_house_from_parsed_line(const struct ParsedLine *parsed_line,
                                 struct Scene *scene)
{
  if (strcmp(parsed_line->tokens[0], "house") != 0)
    return false;
  if (parsed_line->num_tokens != 6)
    report_error_line_wrong_arguments_number("house",
                                             parsed_line->line_number);
  if (!is_valid_id(parsed_line->tokens[1]))
    report_error_invalid_identifier(parsed_line->tokens[1],
                                    parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[2]))
    report_error_invalid_int(parsed_line->tokens[2],
                             parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[3]))
    report_error_invalid_int(parsed_line->tokens[3],
                             parsed_line->line_number);
  if (!is_valid_positive_integer(parsed_line->tokens[4]))
    report_error_invalid_positive_int(parsed_line->tokens[4],
                                      parsed_line->line_number);
  if (!is_valid_positive_integer(parsed_line->tokens[5]))
    report_error_invalid_positive_int(parsed_line->tokens[5],
                                      parsed_line->line_number);
  
  struct Structure house = create_house(
    parsed_line->tokens[1],
    atoi(parsed_line->tokens[2]),
    atoi(parsed_line->tokens[3]),
    atoi(parsed_line->tokens[4]),
    atoi(parsed_line->tokens[5])
  );
  
  add_structure(scene, &house);
  return true;
}

/**
 * Loads an antenna from a parsed line
 *
 * @param parsed_line  The parsed line
 * @param scene        The scene in which the antenna is loaded
 * @return             true if and only if the loading was successful
 */
bool load_antenna_from_parsed_line(const struct ParsedLine* parsed_line,
                                   struct Scene* scene) {
  if (strcmp(parsed_line->tokens[0], "antenna") != 0)
    return false;
  if (parsed_line->num_tokens != 5)
    report_error_line_wrong_arguments_number("antenna",
                                             parsed_line->line_number);
  if (!is_valid_id(parsed_line->tokens[1]))
      report_error_invalid_identifier(parsed_line->tokens[1],
                                      parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[2]))
      report_error_invalid_int(parsed_line->tokens[2],
                               parsed_line->line_number);
  if (!is_valid_integer(parsed_line->tokens[3]))
      report_error_invalid_int(parsed_line->tokens[3],
                               parsed_line->line_number);
  if (!is_valid_positive_integer(parsed_line->tokens[4]))
      report_error_invalid_positive_int(parsed_line->tokens[4],
                                        parsed_line->line_number);
  struct Antenna antenna;
  strncpy(antenna.id, parsed_line->tokens[1], MAX_LENGTH_ID);
  antenna.x = atoi(parsed_line->tokens[2]);
  antenna.y = atoi(parsed_line->tokens[3]);
  antenna.r = atoi(parsed_line->tokens[4]);
  add_antenna(scene, &antenna);
  return true;
}

// Public functions definition
// ===========================

// Helper functions
// ---------------

struct Structure create_building(const char* id, int x, int y, int w, int h) {
  struct Structure building;
  strncpy(building.id, id, MAX_LENGTH_ID);
  building.type = BUILDING;
  building.x = x;
  building.y = y;
  building.w = w;
  building.h = h;
  return building;
}

struct Structure create_house(const char* id, int x, int y, int w, int h) {
  struct Structure house;
  strncpy(house.id, id, MAX_LENGTH_ID);
  house.type = HOUSE;
  house.x = x;
  house.y = y;
  house.w = w;
  house.h = h;
  return house;
}

unsigned int get_num_buildings(const struct Scene* scene) {
  unsigned int count = 0;
  for (unsigned int i = 0; i < scene->num_structures; ++i) {
    if (scene->structures[i].type == BUILDING) {
      count++;
    }
  }
  return count;
}

unsigned int get_num_houses(const struct Scene* scene) {
  unsigned int count = 0;
  for (unsigned int i = 0; i < scene->num_structures; ++i) {
    if (scene->structures[i].type == HOUSE) {
      count++;
    }
  }
  return count;
}

// Construction
// ------------

void initialize_empty_scene(struct Scene* scene) {
  scene->num_structures = 0;
  scene->num_antennas = 0;
}

void load_scene_from_stdin(struct Scene* scene) {
  initialize_empty_scene(scene);
  char line[MAX_LENGTH + 1];
  bool first_line = true, last_line = false;
  int line_number = 1;
  while (fgets(line, MAX_LENGTH, stdin) != NULL) {
    last_line = false;
    line[strcspn(line, "\n")] = '\0';
    if (first_line) {
      if (!is_begin_scene_line(line))
        report_error_scene_first_line();
      first_line = false;
    } else if (is_end_scene_line(line)) {
      last_line = true;
    } else {
      struct ParsedLine parsed_line;
      parse_line(line, &parsed_line, line_number);
      if (parsed_line.num_tokens == 0) {
        report_error("line has no token\n");
      }
      if (!load_building_from_parsed_line(&parsed_line, scene) &&
          !load_house_from_parsed_line(&parsed_line, scene) &&
          !load_antenna_from_parsed_line(&parsed_line, scene)){
            report_error_unrecognized_line(line_number);
          }  
    }
    ++line_number;
  }
  if (!last_line)
    report_error_scene_last_line();
}

// Validation
// ----------

void validate_scene(const struct Scene* scene) {
  struct ValidationError error;
  init_validation_error(&error);
  
  if (!is_scene_valid(scene, &error)) {
    printf("not ok\n");
    fprintf(stderr, "error: %s\n", error.message);
    exit(1);
  }
}

bool are_structures_overlapping(const struct Structure* structure1,
                               const struct Structure* structure2) {
  return are_intervals_overlapping(structure1->x - structure1->w,
                                   structure1->x + structure1->w,
                                   structure2->x - structure2->w,
                                   structure2->x + structure2->w) &&
         are_intervals_overlapping(structure1->y - structure1->h,
                                   structure1->y + structure1->h,
                                   structure2->y - structure2->h,
                                   structure2->y + structure2->h);
}

bool have_antennas_same_position(const struct Antenna* antenna1,
                                const struct Antenna* antenna2) {
  return antenna1->x == antenna2->x && antenna1->y == antenna2->y;
}

bool validate_structures_overlaps(const struct Scene* scene, struct ValidationError* error) {
  for (unsigned int s1 = 0; s1 < scene->num_structures; ++s1) {
    for (unsigned int s2 = s1 + 1; s2 < scene->num_structures; ++s2) {
      const struct Structure* structure1 = scene->structures + s1;
      const struct Structure* structure2 = scene->structures + s2;
      if (are_structures_overlapping(structure1, structure2)) {
        // Format the error message based on structure types
        const char* type1 = structure1->type == BUILDING ? "buildings" : "house";
        snprintf(error->message, sizeof(error->message), 
                "%s %s and %s are overlapping", 
                type1, structure1->id, structure2->id);
        error->has_error = true;
        return true;
      }
    }
  }
  return false;
}

bool validate_antennas(const struct Scene* scene, struct ValidationError* error) {
  for (unsigned int a1 = 0; a1 < scene->num_antennas; ++a1) {
    for (unsigned int a2 = a1 + 1; a2 < scene->num_antennas; ++a2) {
      const struct Antenna* antenna1 = scene->antennas + a1;
      const struct Antenna* antenna2 = scene->antennas + a2;
      if (have_antennas_same_position(antenna1, antenna2)) {
        snprintf(error->message, sizeof(error->message), 
                "antennas %s and %s have the same position", 
                antenna1->id, antenna2->id);
        error->has_error = true;
        return true;
      }
    }
  }
  return false;
}

// Accessors
// ---------

bool scene_is_empty(const struct Scene* scene) {
  return scene->num_structures == 0 && scene->num_antennas == 0;
}

void print_scene_summary(const struct Scene* scene) {
  if (scene_is_empty(scene)) {
    puts("An empty scene");
    return;
  } 
  unsigned int num_buildings = get_num_buildings(scene);
  unsigned int num_houses = get_num_houses(scene);
  printf("A scene with ");
  bool first = true;
  if (num_buildings > 0) {
    printf("%d building%s", num_buildings, num_buildings > 1 ? "s" : "");
    first = false;
  }
  if (num_houses > 0) {
    if (!first) {
      if (scene->num_antennas == 0)
        printf(" and ");
      else
        printf(", ");
    }
    printf("%d house%s", num_houses, num_houses > 1 ? "s" : "");
    first = false;
  }
  if (scene->num_antennas > 0) {
    if (!first)
      printf(" and ");
    printf("%d antenna%s", scene->num_antennas, scene->num_antennas > 1 ? "s" : "");
  }
  printf("\n");
}

void print_scene_structures(const struct Scene* scene) {
  for (unsigned int s = 0; s < scene->num_structures; ++s) {
    const struct Structure* structure = scene->structures + s;
    const char* type_str = structure->type == BUILDING ? "building" : "house";
    printf("  %s %s at %d %d with dimensions %d %d\n",
           type_str, structure->id, structure->x, structure->y, 
           structure->w, structure->h);
  }
}

void print_scene_antennas(const struct Scene* scene) {
  for (unsigned int a = 0; a < scene->num_antennas; ++a) {
    const struct Antenna* antenna = scene->antennas + a;
    printf("  antenna %s at %d %d with range %d\n",
           antenna->id, antenna->x, antenna->y, antenna->r);
  }
}

void print_scene_bounding_box(const struct Scene* scene) {
  if (scene_is_empty(scene)) {
    printf("undefined (empty scene)\n");
    return;
  }
  int xmin = INT_MAX, xmax = INT_MIN,
      ymin = INT_MAX, ymax = INT_MIN;
      
  // Check structures (buildings and houses)
  for (unsigned int s = 0; s < scene->num_structures; ++s) {
    int x = scene->structures[s].x,
        y = scene->structures[s].y,
        w = scene->structures[s].w,
        h = scene->structures[s].h;
    xmin = x - w < xmin ? x - w : xmin;
    xmax = x + w > xmax ? x + w : xmax;
    ymin = y - h < ymin ? y - h : ymin;
    ymax = y + h > ymax ? y + h : ymax;
  }
  // Check antennas
  for (unsigned int a = 0; a < scene->num_antennas; ++a) {
    int x = scene->antennas[a].x,
        y = scene->antennas[a].y,
        r = scene->antennas[a].r;
    xmin = x - r < xmin ? x - r : xmin;
    xmax = x + r > xmax ? x + r : xmax;
    ymin = y - r < ymin ? y - r : ymin;
    ymax = y + r > ymax ? y + r : ymax;
  }
  printf("bounding box [%d, %d] x [%d, %d]\n", xmin, xmax, ymin, ymax);
}

// Modifiers
// ---------

void add_structure(struct Scene* scene, const struct Structure* structure) {
  unsigned int s = 0;
  while (s < scene->num_structures &&
         strcmp(structure->id, scene->structures[s].id) > 0)
    ++s;
  if (s < scene->num_structures &&
      strcmp(structure->id, scene->structures[s].id) == 0) {
    const char* type_str = structure->type == BUILDING ? "building" : "house";
    report_error_non_unique_identifiers(type_str, structure->id);
  }
  for (unsigned int s2 = scene->num_structures; s2 > s; --s2)
    scene->structures[s2] = scene->structures[s2 - 1];
  struct Structure* scene_structure = scene->structures + s;
  strncpy(scene_structure->id, structure->id, MAX_LENGTH_ID);
  scene_structure->type = structure->type;
  scene_structure->x = structure->x;
  scene_structure->y = structure->y;
  scene_structure->w = structure->w;
  scene_structure->h = structure->h;
  ++scene->num_structures;
}

void add_antenna(struct Scene* scene, const struct Antenna* antenna) {
  unsigned int a = 0;
  while (a < scene->num_antennas &&
         strcmp(antenna->id, scene->antennas[a].id) > 0)
    ++a;
  if (a < scene->num_antennas &&
      strcmp(antenna->id, scene->antennas[a].id) == 0)
    report_error_non_unique_identifiers("antenna", antenna->id);
  for (unsigned int a2 = scene->num_antennas; a2 > a; --a2)
    scene->antennas[a2] = scene->antennas[a2 - 1];
  struct Antenna* scene_antenna = scene->antennas + a;
  strncpy(scene_antenna->id, antenna->id, MAX_LENGTH_ID);
  scene_antenna->x = antenna->x;
  scene_antenna->y = antenna->y;
  scene_antenna->r = antenna->r;
  ++scene->num_antennas;
}

// Coverage quality functions
// -------------------------

/**
 * Calculates the squared distance between two points.
 * This avoids using square root for efficiency when comparing distances.
 *
 * @param x1  x-coordinate of the first point
 * @param y1  y-coordinate of the first point
 * @param x2  x-coordinate of the second point
 * @param y2  y-coordinate of the second point
 * @return    The squared distance between the points
 */
static int distance_squared(int x1, int y1, int x2, int y2) {
  int dx = x1 - x2;
  int dy = y1 - y2;
  
  return dx * dx + dy * dy;
}



