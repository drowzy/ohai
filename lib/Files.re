
let bin_files info => {
  open Info.T;
  let ext = info.reason ? ".re" : ".ml";

  [
    ("bin/jbuild", Templates.Bin.jbuild info.name),
    ("bin/" ^ info.name ^ ext, (
      info.reason ? Templates.Bin.re : Templates.Bin.ml
    )),
    ("lib/jbuild", Templates.Bin.Lib.jbuild),
    ("lib/Main" ^ ext, (
      info.reason ? Templates.Bin.Lib.re : Templates.Bin.Lib.ml
    )),
    ("test/jbuild", Templates.Bin.Test.jbuild),
    ("test/test." ^ ext, (
      info.reason ? Templates.Bin.Test.re : Templates.Bin.Test.ml
    )),
  ]
};

let lib_files info => {
  open Info.T;
  let ext = info.reason ? ".re" : ".ml";

  [
    ("lib/jbuild", Templates.Lib.jbuild info.name),
    ("lib/" ^ info.name ^ ext, (
      info.reason ? Templates.Lib.re : Templates.Lib.ml
    )),
    ("test/jbuild", Templates.Lib.Test.jbuild info.name),
    ("test/test." ^ ext,
      (info.reason ? Templates.Lib.Test.re : Templates.Lib.Test.ml)
      info.name),
  ]
};

let generate info => {
  open Info.T;
  [
    (info.name ^ ".opam", Opam.build info),
    (".gitignore", Templates.gitignore),
    ...((info.executable ? bin_files : lib_files) info)
  ]
};