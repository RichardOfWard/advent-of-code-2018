type claim = {
  id: int,
  left: int,
  top: int,
  width: int,
  height: int,
};

let parse = (t: string) => {
  let splitter = Js.Re.fromStringWithFlags("#| @ |,|: |x", ~flags="g");
  let nums =
    Js.String.replaceByRe(splitter, " ", t)
    |> Js.String.trim
    |> Js.String.split(" ");
  switch (nums) {
  | [|id, left, top, width, height|] => {
      id: int_of_string(id),
      left: int_of_string(left),
      top: int_of_string(top),
      width: int_of_string(width),
      height: int_of_string(height),
    }
  | _ => raise(Tokens.BadInput(t))
  };
};

let claims = Tokens.load_file("res/03.txt", parse);

let total_height =
  claims
  |> Array.map(c => c.top + c.height)
  |> Array.fold_left(Js.Math.max_int, 0);
let total_width =
  claims
  |> Array.map(c => c.left + c.width)
  |> Array.fold_left(Js.Math.max_int, 0);

let claim_counts = Array.make_matrix(total_width, total_height, 0);

Array.iter(
  c =>
    for (x in c.left to c.left + c.width - 1) {
      for (y in c.top to c.top + c.height - 1) {
        let current = claim_counts[x][y];
        claim_counts[x][y] = current + 1;
      };
    },
  claims,
);

let answer1 =
  Array.fold_left(
    (total, column) =>
      Array.fold_left((a, b) => b >= 2 ? a + 1 : a, 0, column) + total,
    0,
    claim_counts,
  );

Js.log(answer1);

let unique_claims =
  Js.Array.filter(
    c => {
      let unique = ref(true);
      for (x in c.left to c.left + c.width - 1) {
        for (y in c.top to c.top + c.height - 1) {
          if (claim_counts[x][y] > 1) {
            unique := false;
          };
        };
      };
      unique^;
    },
    claims,
  );

Assert.assert_equal(1, Array.length(unique_claims));

let answer2 = unique_claims[0].id;

Js.log(answer2);

Assert.assert_equal(909, answer2);
