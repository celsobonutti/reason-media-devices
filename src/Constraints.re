type constrain('a) =
  | Simple('a)
  | Constrain({
      exact: option('a),
      ideal: option('a),
    });

type constrainWithArray('a) =
  | Simple('a)
  | Array(array('a))
  | Constrain({
      exact: option('a),
      ideal: option('a),
    });

let map = (functor_: constrain('a), function_: 'a => 'b): constrain('b) => {
  switch (functor_) {
  | Simple(c) => Simple(function_(c))
  | Constrain({exact, ideal}) =>
    Constrain({
      exact: Belt.Option.map(exact, c => function_(c)),
      ideal: Belt.Option.map(ideal, c => function_(c)),
    })
  };
};

let mapWithArray =
    (functor_: constrainWithArray('a), function_: 'a => 'b)
    : constrainWithArray('b) => {
  switch (functor_) {
  | Simple(c) => Simple(function_(c))
  | Constrain({exact, ideal}) =>
    Constrain({
      exact: Belt.Option.map(exact, c => function_(c)),
      ideal: Belt.Option.map(ideal, c => function_(c)),
    })
  | Array(elements) => Array(Belt.Array.map(elements, el => function_(el)))
  };
};

module Audio = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    autoGainControl: constrain(bool),
    [@bs.optional]
    channelCount: constrain(int),
    [@bs.optional]
    echoCancellation: constrain(bool),
    [@bs.optional]
    latency: constrain(float),
    [@bs.optional]
    noiseSuppression: constrain(bool),
    [@bs.optional]
    sampleRate: constrain(int),
    [@bs.optional]
    sampleSize: constrain(int),
    [@bs.optional]
    volume: constrain(float),
  };

  let make = t;
};

module Video = {
  [@bs.deriving jsConverter]
  type facingModeOption = [ | `user | `environment | `left | `right];

  type facingMode = constrainWithArray(facingModeOption);

  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    aspectRatio: constrain(float),
    [@bs.optional]
    facingMode: Js.Nullable.t(constrainWithArray(string)),
    [@bs.optional]
    frameRate: constrain(float),
    [@bs.optional]
    height: constrain(int),
    [@bs.optional]
    width: constrain(int),
  };

  let make =
      (
        ~aspectRatio: option(constrain(float))=?,
        ~frameRate: option(constrain(float))=?,
        ~height: option(constrain(int))=?,
        ~width: option(constrain(int))=?,
        ~facingMode: option(constrainWithArray(facingModeOption))=?,
        (),
      ) => {
    t(
      ~aspectRatio?,
      ~frameRate?,
      ~height?,
      ~width?,
      ~facingMode=
        facingMode->Belt.Option.mapWithDefault(
          Js.Nullable.null, facingModeConstrain =>
          mapWithArray(facingModeConstrain, facingModeOptionToJs)
          ->Js.Nullable.return
        ),
      (),
    );
  };
};
