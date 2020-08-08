let audioConstraints =
  Constraints.Audio.make(
    ~autoGainControl=Constraints.ConstrainBoolean.makeSimple(true),
    ~latency={
      min: Some(0.),
      max: Some(60.),
      ideal: Some(30.),
      exact: None,
    },
    (),
  );

let videoConstraints =
  Constraints.Video.make(
    ~facingMode=(Single, {ideal: Some("user"), exact: None}),
    (),
  );

// JS.Promise.t('a) examples

let jsConstraintExample =
  MediaDevices.getJsPromiseUserMedia(
    Constraint,
    Constraint,
    {audio: audioConstraints, video: videoConstraints},
  );

let jsBooleanExample =
  MediaDevices.getJsPromiseUserMedia(Bool, Bool, {audio: false, video: true});

let jsMixedExample =
  MediaDevices.getJsPromiseUserMedia(
    Bool,
    Constraint,
    {audio: true, video: videoConstraints},
  );

// Promise.t('a)

let constraintExample = MediaDevices.getUserMedia(
  ~audio=Constraint(audioConstraints),
  ~video=Constraint(videoConstraints)
);

let booleanExample = MediaDevices.getUserMedia(
  ~audio=Bool(false),
  ~video=Bool(true)
);

let mixedExample = MediaDevices.getUserMedia(
  ~audio=Bool(true),
  ~video=Constraint(videoConstraints)
);