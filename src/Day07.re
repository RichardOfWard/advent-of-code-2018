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
        let candidates = unsorted^
            |> List.filter(
                step => blockers^
                  |> List.map(((_, blockee)) => blockee)
                  |> List.filter(blockee => blockee == step)
                  |> List.length
                  |> l => l == 0
            );
        switch(candidates) {
        | [candidate, ..._] => {
            sorted := List.append(sorted^, [candidate]);
            unsorted := List.filter(s => s != candidate, unsorted^);
            blockers := List.filter(((blocker, _)) => blocker != candidate, blockers^);
          }
        | [] => raise(Unsortable);
        }
    }
    sorted^
}

let answer1 = string_topo_sort(blockers, steps) |> List.fold_left(a=>b=>Js.String.concat(b, a), "");

Js.log(answer1);

Assert.assert_equal(answer1, "GDHOSUXACIMRTPWNYJLEQFVZBK")
