type state =
  | Asleep
  | Awake;
type action =
  | StartGuarding(string)
  | ChangeState(state);
type event = {
  date_time: Js.Date.t,
  action,
};

let parse = (t: string) => {
  let splitter = Js.Re.fromStringWithFlags("\\[|] ", ~flags="g");
  let strings = Js.String.splitByRe(splitter, t);
  let date_time = Js.Date.fromString(strings[1]);
  let action =
    switch (strings[2]) {
    | "falls asleep" => ChangeState(Asleep)
    | "wakes up" => ChangeState(Awake)
    | message => StartGuarding(message)
    };
  {date_time, action};
};

let events = Tokens.load_file("res/04.txt", parse);

Array.sort(
  (a, b) =>
    String.compare(
      Js.Date.toISOString(a.date_time),
      Js.Date.toISOString(b.date_time),
    ),
  events,
);

module StringMap = Map.Make(String);
type string_to_int_array = StringMap.t(array(int));

let guard_log: ref(string_to_int_array) = ref(StringMap.empty);

Array.iter(
  event =>
    switch (event.action) {
    | StartGuarding(guard) =>
      guard_log := StringMap.add(guard, Array.make(60, 0), guard_log^)
    | _ => ()
    },
  events,
);

let guard_log = guard_log^;

let current_guard = ref("nobody");

Array.iter(
  event =>
    switch (event.action) {
    | StartGuarding(guard) => current_guard := guard
    | ChangeState(state) =>
      let log = StringMap.find(current_guard^, guard_log);
      for (minute in int_of_float(Js.Date.getMinutes(event.date_time)) to 59) {
        log[minute] =
          log[minute]
          + (
            switch (state) {
            | Asleep => 1
            | Awake => (-1)
            }
          );
      };
    },
  events,
);

let sleepiest_guard = ref("nobody");
let sleep_amount = ref(0);

StringMap.iter(
  (guard, log) => {
    let guard_sleep_amount = Array.fold_left((a, b) => a + b, 0, log);
    if (guard_sleep_amount > sleep_amount^) {
      sleepiest_guard := guard;
      sleep_amount := guard_sleep_amount;
    };
  },
  guard_log,
);
let sleepiest_guard = sleepiest_guard^;

let sleepiest_guard_log = StringMap.find(sleepiest_guard, guard_log);

let sleepiest_minute_amount =
  Array.fold_left((a, b) => a > b ? a : b, 0, sleepiest_guard_log);

let sleepiest_minute = Js.Array.indexOf(sleepiest_minute_amount, sleepiest_guard_log);

Js.log("answer 1");
Js.log(sleepiest_guard);
Js.log("*");
Js.log(sleepiest_minute);
Assert.assert_equal("Guard #2953 begins shift", sleepiest_guard);
Assert.assert_equal(sleepiest_minute, 39)

let sleepiest_guard = ref("nobody");
let sleep_amount = ref(0);
let sleepiest_minute = ref(0);

StringMap.iter(
  (guard, log) => {
    let guard_sleepiest_minute_amount = Array.fold_left((a, b) => a > b ? a : b, 0, log);
    if (guard_sleepiest_minute_amount > sleep_amount^) {
      sleepiest_guard := guard;
      sleep_amount := guard_sleepiest_minute_amount;
      sleepiest_minute := Js.Array.indexOf(guard_sleepiest_minute_amount, log);
    };
  },
  guard_log,
);
let sleepiest_guard = sleepiest_guard^;
let sleepiest_minute = sleepiest_minute^;

Js.log("answer 2");
Js.log(sleepiest_guard);
Js.log("*");
Js.log(sleepiest_minute);
Assert.assert_equal("Guard #1069 begins shift", sleepiest_guard);
Assert.assert_equal(sleepiest_minute, 30)
