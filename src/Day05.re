let tokens = Tokens.load_file("res/05.txt", Js.String.split(""))[0];

let react_once = input =>
  Array.fold_left(
    (output, cur) => {
      let len = Array.length(output);
      let prev = len > 0 ? Some(output[len-1]) : None;
      switch (prev) {
      | Some(prev) =>
      let curUpper = Js.String.toLocaleUpperCase(cur);
      let prevUpper = Js.String.toLocaleUpperCase(prev);
        if (cur != prev && curUpper == prevUpper) {
          Js.Array.slice(~start=0, ~end_=-1, output);
        } else {
          Js.Array.concat(Js.String.split("", cur), output);
        }
      | None =>  Js.Array.concat(Js.String.split("", cur), output);
      };
    },
    [||],
    input
  );

let rec react_many = input => {
    let next = react_once(input);
    if (input == next) {
        next;
    } else {
        react_many(next);
    }
}

Js.log(Array.length(react_many(tokens)));
