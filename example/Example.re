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
    ~facingMode=
      Constraints.ConstrainDOMString.make(
        Array,
        {ideal: Some([|"test", "this", "shit"|]), exact: None},
      ),
    (),
  );

let constraintExample =
  MediaDevices.getUserMedia(
    Constraint,
    Constraint,
    {audio: audioConstraints, video: videoConstraints},
  );

let booleanExample =
  MediaDevices.getUserMedia(Bool, Bool, {audio: false, video: true});

let mixedExample =
  MediaDevices.getUserMedia(
    Bool,
    Constraint,
    {audio: true, video: videoConstraints},
  );
