type audioConstraints = bool;
type videoConstraints = bool;
  
type constraints = {
  audio: option(audioConstraints),
  video: option(videoConstraints),
};

[@bs.val] [@bs.scope ("window", "navigator", "mediaDevices")]
external getUserMedia: constraints => Js.Promise.t(MediaStream.t) =
  "getUserMedia";
