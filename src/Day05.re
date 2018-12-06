let tokens = Tokens.load_file("res/05.txt", Js.String.split(""))[0];

let react_once = input =>
  Array.fold_left(
    (output, cur) => {
      let len = Array.length(output);
      let prev = len > 0 ? Some(output[len - 1]) : None;
      switch (prev) {
      | Some(prev) =>
        let curUpper = Js.String.toLocaleUpperCase(cur);
        let prevUpper = Js.String.toLocaleUpperCase(prev);
        if (cur != prev && curUpper == prevUpper) {
          Js.Array.slice(~start=0, ~end_=-1, output);
        } else {
          Js.Array.concat(Js.String.split("", cur), output);
        };
      | None => Js.Array.concat(Js.String.split("", cur), output)
      };
    },
    [||],
    input,
  );

let rec react_many = input => {
  let next = react_once(input);
  if (input == next) {
    next;
  } else {
    react_many(next);
  };
};

let answer1 = Array.length(react_many(tokens));
Js.log(answer1);
Assert.assert_equal(answer1, 9060);

let tried_solution_lengths =
  Js.String.split("", "abcdefghijklmnopqrstuvwxyz")
  |> Array.map(letter =>
       Array.length(
         react_many(
           Js.Array.filter(
             e => Js.String.toLocaleLowerCase(e) != letter,
             tokens,
           ),
         ),
       )
     );

let answer2 =
  Array.fold_left(
    (best, current) => current < best ? current : best,
    Array.length(tokens),
    tried_solution_lengths,
  );

Js.log(answer2);
