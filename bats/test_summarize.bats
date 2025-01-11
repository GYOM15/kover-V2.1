setup() {
  load 'bats-support/load'
  load 'bats-assert/load'
  root_dir="$(cd "$( dirname "$BATS_TEST_FILENAME" )/.." >/dev/null 2>&1 && pwd)"
  PATH="$root_dir/bin:$PATH"
  examples_dir="$root_dir/examples"
}

# Normal usage
# ------------

@test "kover summarize runs correctly on an empty scene" {
  run kover summarize < "$examples_dir"/empty.scene
  assert_success
  assert_output "An empty scene"
}

@test "kover summarize runs correctly on a scene with 1 building" {
  run kover summarize < "$examples_dir"/1b.scene
  assert_success
  assert_output "A scene with 1 building"
}

@test "kover summarize runs correctly on a scene with 2 buildings" {
  run kover summarize < "$examples_dir"/2b.scene
  assert_success
  assert_output "A scene with 2 buildings"
}

@test "kover summarize runs correctly on a scene with 1 antenna" {
  run kover summarize < "$examples_dir"/1a.scene
  assert_success
  assert_output "A scene with 1 antenna"
}

@test "kover summarize runs correctly on a scene with 2 antennas" {
  run kover summarize < "$examples_dir"/2a.scene
  assert_success
  assert_output "A scene with 2 antennas"
}

@test "kover summarize runs correctly on a scene with 1 building and 1 antenna" {
  run kover summarize < "$examples_dir"/1b1a.scene
  assert_success
  assert_output "A scene with 1 building and 1 antenna"
}

# Wrong usage
# -----------

@test "kover summarize reports an error when first line is invalid" {
  run kover summarize < "$examples_dir"/first_line.invalid
  assert_failure
  assert_output "error: first line must be exactly 'begin scene'"
}

@test "kover summarize reports an error when a line is unrecognized" {
  run kover summarize < "$examples_dir"/unrecognized_line.invalid
  assert_failure
  assert_output "error: unrecognized line (line #2)"
}

@test "kover summarize reports an error when last line is not 'end scene'" {
  run kover summarize < "$examples_dir"/no_end_scene.invalid
  assert_failure
  assert_output "error: last line must be exactly 'end scene'"
}

@test "kover summarize reports an error when two buildings have same id" {
  run kover summarize < "$examples_dir"/2b_non_unique_id.invalid
  assert_failure
  assert_output "error: building identifier b1 is non unique"
}

@test "kover summarize reports an error when two buildings are overlapping" {
  run kover summarize < "$examples_dir"/2b_overlapping.invalid
  assert_failure
  assert_output "error: buildings b1 and b2 are overlapping"
}
