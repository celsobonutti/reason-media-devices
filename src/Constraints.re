module ConstrainBoolean = {
  type t = {
    exact: option(bool),
    ideal: option(bool),
  };

  let makeSimple = value => {
    {exact: None, ideal: Some(value)};
  };
};

module ConstrainDouble = {
  type t = {
    exact: option(float),
    ideal: option(float),
    min: option(float),
    max: option(float),
  };

  let makeSimple = value => {
    {ideal: Some(value), exact: None, min: None, max: None};
  };
};

module ConstrainULong = {
  type t = {
    exact: option(int),
    ideal: option(int),
    min: option(int),
    max: option(int),
  };

  let makeSimple = value => {
    {ideal: Some(value), exact: None, min: None, max: None};
  };
};

module ConstrainDOMString = {
  type fields('a) = {
    exact: option('a),
    ideal: option('a),
  };

  type domString(_) =
    | Single: domString(fields(string))
    | Array: domString(fields(array(string)));

  type t('a) = 'a;

  let make: (domString('a), 'a) => 'a = (_kind, value) => value;
};

// NOTE: Won't work for now. Wait until bucklescript implements automatic
// mapping from polyvars to JS strings.
module type DOMStringOptions = {type t;};

module LimitedDOMString = (Options: DOMStringOptions) => {
  type fields('a) = {
    exact: option('a),
    ideal: option('a),
  };

  type fieldVariants(_) =
    | Single: fieldVariants(fields(Options.t))
    | Array: fieldVariants(fields(array(Options.t)));

  type t('a) = 'a;

  let make: (fieldVariants('a), 'a) => 'a = (_kind, value) => value;
};

module FacingMode = {
  type t = [ | `user | `environment | `left | `right];
};

module ConstrainFacingMode = LimitedDOMString(FacingMode);

module Audio = {
  type t = {
    autoGainControl: option(ConstrainBoolean.t),
    echoCancellation: option(ConstrainBoolean.t),
    noiseSuppression: option(ConstrainBoolean.t),
    latency: option(ConstrainDouble.t),
    volume: option(ConstrainDouble.t),
    channelCount: option(ConstrainULong.t),
    sampleRate: option(ConstrainULong.t),
    sampleSize: option(ConstrainULong.t),
  };

  let make =
      (
        ~autoGainControl=?,
        ~echoCancellation=?,
        ~noiseSuppression=?,
        ~latency=?,
        ~volume=?,
        ~channelCount=?,
        ~sampleRate=?,
        ~sampleSize=?,
        (),
      ) => {
    {
      autoGainControl,
      echoCancellation,
      noiseSuppression,
      latency,
      volume,
      channelCount,
      sampleRate,
      sampleSize,
    };
  };
};

module Video = {
  type t('a) = {
    aspectRatio: option(ConstrainDouble.t),
    facingMode: option(ConstrainDOMString.t('a)),
    frameRate: option(ConstrainDouble.t),
    height: option(ConstrainULong.t),
    width: option(ConstrainULong.t),
  };

  let make =
      (
        ~aspectRatio=?,
        ~frameRate=?,
        ~height=?,
        ~width=?,
        ~facingMode: option((ConstrainDOMString.domString('a), 'a))=?,
        (),
      ) => {
    let facing =
      switch (facingMode) {
      | None => None
      | Some((kind_, value)) => Some(ConstrainDOMString.make(kind_, value))
      };
    {aspectRatio, frameRate, height, width, facingMode: facing};
  };
};
