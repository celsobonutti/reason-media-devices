type videoConstraint_('a) =
  | Bool: videoConstraint_(bool)
  | Constraint: videoConstraint_(Constraints.Video.t('a));

type audioConstraint_(_) =
  | Bool: audioConstraint_(bool)
  | Constraint: audioConstraint_(Constraints.Audio.t);

type constraints('audio, 'video) = {
  audio: 'audio,
  video: 'video,
};

[@bs.val] [@bs.scope ("window", "navigator", "mediaDevices")]
external getJsPromiseUserMedia:
  (
    [@bs.ignore] audioConstraint_('audio),
    [@bs.ignore] videoConstraint_('video),
    constraints('audio, 'video)
  ) =>
  Js.Promise.t(MediaStream.t) =
  "getUserMedia";

type videoConstraint('a) =
  | Bool(bool)
  | Constraint(Constraints.Video.t('a));

type audioConstraint =
  | Bool(bool)
  | Constraint(Constraints.Audio.t);

let getUserMedia = (~audio: audioConstraint, ~video: videoConstraint('a)) => {
  (
    switch (audio, video) {
    | (Bool(audio), Bool(video)) =>
      getJsPromiseUserMedia(Bool, Bool, {audio, video})
    | (Bool(audio), Constraint(video)) =>
      getJsPromiseUserMedia(Bool, Constraint, {audio, video})
    | (Constraint(audio), Bool(video)) =>
      getJsPromiseUserMedia(Constraint, Bool, {audio, video})
    | (Constraint(audio), Constraint(video)) =>
      getJsPromiseUserMedia(Constraint, Constraint, {audio, video})
    }
  )
  |> Promise.Js.fromBsPromise
  |> Promise.Js.toResult;
};
