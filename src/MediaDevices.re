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
external getUserMedia:
  (
    [@bs.ignore] audioConstraint_('audio),
    [@bs.ignore] videoConstraint_('video),
    constraints('audio, 'video)
  ) =>
  Promise.t(MediaStream.t) =
  "getUserMedia";
