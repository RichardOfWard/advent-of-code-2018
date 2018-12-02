exception TestFailure(string);

let assert_equal = (actual, expected) =>
  if (actual != expected) {
    Js.log("Test Failure! Expected:");
    Js.log(expected);
    Js.log("But found:");
    Js.log(actual);
    raise(TestFailure("Test Failure"));
  };
