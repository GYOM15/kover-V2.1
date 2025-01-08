setup() {
  load 'bats-support/load'
  load 'bats-assert/load'
  root_dir="$(cd "$( dirname "$BATS_TEST_FILENAME" )/.." >/dev/null 2>&1 && pwd)"
  PATH="$root_dir/bin:$PATH"
  examples_dir="$root_dir/examples"
}

@test "kover describe runs correctly on an empty scene" {
  run kover describe < "$examples_dir"/empty.scene
  assert_success
  assert_output "An empty scene"
}

@test "kover describe runs correctly on a scene with one building" {
  run kover describe < "$examples_dir"/1b.scene
  assert_success
  assert_line --index 0 "A scene with 1 building"
  assert_line --index 1 "  building b1 at 0 0 with dimensions 1 1"
}
