let load_file = (filename: string, parse: (string => 'a)) => {
  let file = Node.Fs.readFileAsUtf8Sync(filename);
  let re = Js.Re.fromString("(?: |\t|\r\n|\n|\r)+");
  Js.String.splitByRe(re, file)
  |> Array.map(String.trim)
  |> Js.Array.filter(t => t !== "")
  |> Array.map(parse);
};
