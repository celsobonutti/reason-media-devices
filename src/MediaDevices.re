type constrain('a) =
  | Simple('a)
  | Constrain({
      exact: 'a,
      ideal: 'a,
    });

module AudioConstraints = {
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
};

module VideoConstraints = {
  [@bs.deriving jsConverter]
  type facingModeOption = [ | `user | `environment | `left | `right];

  type facingMode =
    | Array(array(facingModeOption))
    | Constrain(constrain(facingModeOption));

  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    aspectRatio: constrain(float),
    [@bs.optional]
    facingMode,
    [@bs.optional]
    frameRate: constrain(float),
    [@bs.optional]
    height: constrain(int),
    [@bs.optional]
    width: constrain(int),
  };
};

[@bs.deriving accessors]
type audioConstraints =
  | Boolean(bool)
  | Constraints(AudioConstraints.t);

[@bs.deriving accessors]
type videoConstraints =
  | Boolean(bool)
  | Constraints(VideoConstraints.t);

type constraints = {
  audio: option(audioConstraints),
  video: option(videoConstraints),
};

[@bs.val] [@bs.scope ("window", "navigator", "mediaDevices")]
external userMedia: constraints => Js.Promise.t(MediaStream.t) =
  "getUserMedia";

let getUserMedia = (~audio=?, ~video=?, ()) => {
  userMedia({audio, video});
};
