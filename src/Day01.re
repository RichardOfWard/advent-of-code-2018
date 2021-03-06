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
  Tokens.load_file("res/01.txt", parse_delta)
  |> Array.fold_left(add_delta, 0);

Js.log("1.1 = " ++ string_of_int(answer1));

Assert.assert_equal(answer1, 439);

/* Part two */

let deltas = Tokens.load_file("res/01.txt", parse_delta);
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

Assert.assert_equal(answer2, 124645);
