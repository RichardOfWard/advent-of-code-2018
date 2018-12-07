type point = {
  x: int,
  y: int,
};

let locations =
  Tokens.load_file("res/06.txt", t => {
    let split = Js.String.split(", ", t);
    {x: int_of_string(split[0]), y: int_of_string(split[1])};
  });

let min = {x: (-1000), y: (-1000)};

let max = {x: 1000, y: 1000};

let nearest_locations_map =
  Array.make_matrix(
    max.x - min.x + 1,
    max.y - min.y + 1,
    None: option(point),
  );

let manhatten_distance = (p1, p2) =>
  Js.Math.abs_int(p1.x - p2.x) + Js.Math.abs_int(p1.y - p2.y);

type found_location =
  | ClosestTo(point, int)
  | OnBoundary(int);

for (x in min.x to max.x) {
  for (y in min.y to max.y) {
    let nearest_location =
      locations
      |> Array.map(l => (l, manhatten_distance(l, {x, y})))
      |> Array.fold_left(
           (found, (l, d)) =>
             switch (found) {
             | OnBoundary(nd) => d < nd ? ClosestTo(l, d) : OnBoundary(nd)
             | ClosestTo(nl, nd) =>
               if (d < nd) {
                 ClosestTo(nl, d);
               } else if (d === nd) {
                 OnBoundary(d);
               } else {
                 ClosestTo(nl, nd);
               }
             },
           OnBoundary(99999),
         );
    nearest_locations_map[x - min.x][y - min.y] = (
      switch (nearest_location) {
      | ClosestTo(l, _) => Some(l)
      | OnBoundary(_) => None
      }
    );
  };
};

module PointSet =
  Set.Make({
    type t = point;
    let compare = Pervasives.compare;
  });

let edge_locations = ref(PointSet.empty);

for (x in min.x to max.x) {
  for (y in min.y to max.y) {
    if (x == min.x || y == min.y || x == max.x || y == max.y) {
      switch (nearest_locations_map[x - min.x][y - min.y]) {
      | Some(location) =>
        edge_locations := PointSet.add(location, edge_locations^)
      | None => ()
      };
    };
  };
};
let edge_locations = edge_locations^;

let farthest_finite_location_size =
  locations
  |> Array.fold_left(
       (flc, l) => {
         let lc = ref(0);
         if (!PointSet.exists(tl => l == tl, edge_locations)) {
           for (x in min.x to max.x) {
             for (y in min.y to max.y) {
               switch (nearest_locations_map[x - min.x][y - min.y]) {
               | Some(tl) =>
                 if (tl == l) {
                   lc := lc^ + 1;
                 }
               | None => ()
               };
             };
           };
         };
         lc^ > flc ? lc^ : flc;
       },
       0,
     );

Js.log(farthest_finite_location_size);
