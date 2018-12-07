let blockers =
  Tokens.load_file("res/07.txt", t => {
    let words = Js.String.split(" ", t);
    (words[1], words[7]);
  })
  |> Array.to_list;

module StringMap = Map.Make(String);
module StringSet = Set.Make(String);

let steps =
  blockers
  |> List.fold_left((steps, (s1, s2)) => [s1, s2, ...steps], [])
  |> StringSet.of_list
  |> StringSet.elements
  |> List.sort(Pervasives.compare);

exception Unsortable;

let string_topo_sort = (blockers, steps) => {
  let sorted = ref([]);
  let unsorted = ref(steps);
  let blockers = ref(blockers);
  while (unsorted^ != []) {
    let candidates =
      unsorted^
      |> List.filter(step =>
           blockers^
           |> List.map(((_, blockee)) => blockee)
           |> List.filter(blockee => blockee == step)
           |> List.length
           |> (l => l == 0)
         );
    switch (candidates) {
    | [candidate, ..._] =>
      sorted := List.append(sorted^, [candidate]);
      unsorted := List.filter(s => s != candidate, unsorted^);
      blockers :=
        List.filter(((blocker, _)) => blocker != candidate, blockers^);
    | [] => raise(Unsortable)
    };
  };
  sorted^;
};

let answer1 =
  string_topo_sort(blockers, steps)
  |> List.fold_left((a, b) => Js.String.concat(b, a), "");

Js.log(answer1);

Assert.assert_equal(answer1, "GDHOSUXACIMRTPWNYJLEQFVZBK");

type step = {
  label: string,
  remaining: int,
};

let calculate_work_time = (blockers, steps, num_elves) => {
  let remaining_steps = ref(steps);
  let blockers = ref(blockers);
  let seconds_elapsed = ref(0);
  let elf_steps = Array.make(num_elves, None);
  let finished = ref(false);
  while (! finished^) {
    let working_elves =
      Js.Array.filter(e => e !== None, elf_steps) |> Array.length;
    let remaining_step_count = List.length(remaining_steps^);
    if (working_elves + remaining_step_count > 0) {
      for (e in 0 to num_elves - 1) {
        elf_steps[e] = (
          switch (elf_steps[e]) {
          | None =>
            let candidates =
              remaining_steps^
              |> List.filter(step =>
                   blockers^
                   |> List.map(((_, blockee)) => blockee)
                   |> List.filter(blockee => blockee == step.label)
                   |> List.length
                   |> (l => l == 0)
                 );
            switch (candidates) {
            | [candidate, ..._] =>
              remaining_steps :=
                List.filter(s => s != candidate, remaining_steps^);
              Some(candidate);
            | _ => None
            };
          | Some(step) => Some(step)
          }
        );
      };
      seconds_elapsed := seconds_elapsed^ + 1;
      for (e in 0 to num_elves - 1) {
        elf_steps[e] = (
          switch (elf_steps[e]) {
          | None => None
          | Some({label, remaining: 1}) =>
            blockers :=
              List.filter(((blocker, _)) => blocker != label, blockers^);
            None;
          | Some({label, remaining}) =>
            Some({label, remaining: remaining - 1})
          }
        );
      };
    } else {
      finished := true;
    };
  };
  seconds_elapsed^;
};

let steps_with_work = {
  let i = ref(60);
  List.map(
    step => {
      i := i^ + 1;
      {label: step, remaining: i^};
    },
    steps,
  );
};

let answer2 = calculate_work_time(blockers, steps_with_work, 5);
Js.log(answer2);
Assert.assert_equal(answer2, 1024);
