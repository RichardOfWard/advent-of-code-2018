let loadTokens = (filename: string) => {
  let file = Node.Fs.readFileAsUtf8Sync(filename);
  let re = Js.Re.fromString("(?: |\t|\r\n|\n|\r)+");
  Js.String.splitByRe(re, file)
  |> Js.Array.map(String.trim)
  |> Js.Array.filter(t => t !== "");
};

exception BadInput(string);

type direction =
  | Positive
  | Negative;

let parse_direction = (token: string) =>
  switch (String.sub(token, 0, 1)) {
  | "-" => Negative
  | "+" => Positive
  | c => raise(BadInput(c))
  };

let parse_value = (token: string) =>
  int_of_string(String.sub(token, 1, String.length(token) - 1));

type delta = {
  direction,
  value: int,
};

let parse_delta = (token: string): delta => {
  direction: parse_direction(token),
  value: parse_value(token),
};

let add_delta = (i: int, d: delta) =>
  switch (d.direction) {
  | Positive => i + d.value
  | Negative => i - d.value
  };

let answer1 =
  loadTokens("res/01.txt")
  |> Array.map(parse_delta)
  |> Array.fold_left(add_delta, 0);

Js.log("1.1 = " ++ string_of_int(answer1));

exception TestFailure(string);

let testEqual = (actual, expected) =>
  if (actual != expected) {
    Js.log("Test Failure! Expected:");
    Js.log(expected);
    Js.log("But found:");
    Js.log(actual);
    raise(TestFailure("Test Failure"));
  };

testEqual(answer1, 439);

/* Part two */

let deltas = loadTokens("res/01.txt") |> Array.map(parse_delta);
let found = ref(false);
let visited = ref([0]);
let i = ref(0);

while (! found^) {
  let next = add_delta(List.nth(visited^, 0), deltas[i^]);
  if (List.length(List.find_all(v => v == next, visited^)) > 0) {
    found := true;
  } else {
    i := i^ + 1;
    if (i^ == Array.length(deltas)) {
      i := 0;
    };
  };
  visited := [next, ...visited^];
};

let answer2: int = List.nth(visited^, 0);
Js.log("1.2 = " ++ string_of_int(answer2));
