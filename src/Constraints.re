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
  type t = {
    exact: option(array(string)),
    ideal: option(array(string)),
  };

  let makeSimple = value => {
    {ideal: Some(value), exact: None};
  };
};

module type DOMStringOptions = {type t;};

module LimitedDOMString = (Options: DOMStringOptions) => {
  type t = {
    exact: option(array(Options.t)),
    ideal: option(array(Options.t)),
  };

  let makeSimple = value => {
    {ideal: Some(value), exact: None};
  };
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
    facingMode: option(ConstrainFacingMode.t),
    frameRate: option(ConstrainDouble.t),
    height: option(ConstrainULong.t),
    width: option(ConstrainULong.t),
  };

  let make =
      (~aspectRatio=?, ~frameRate=?, ~height=?, ~width=?, ~facingMode=?, ()) => {
    {aspectRatio, frameRate, height, width, facingMode};
  };
};
