#pragma once

class PidController {
 public:
  PidController(float kp, float ki, float kd) : kp_(kp), ki_(ki), kd_(kd) {}

  void setSetpoint(float value) { setpoint_ = value; }
  float setpoint() const { return setpoint_; }
  void setLimits(float lo, float hi) { lo_ = lo; hi_ = hi; }

  float update(float setpoint, float measured, float dt) {
    float error = setpoint - measured;
    integral_ += error * dt;
    float derivative = (error - last_error_) / dt;
    last_error_ = error;
    float raw = kp_ * error + ki_ * integral_ + kd_ * derivative;
    if (raw < lo_) return lo_;
    if (raw > hi_) return hi_;
    return raw;
  }

 private:
  float kp_;
  float ki_;
  float kd_;
  float setpoint_ = 0.0f;
  float integral_ = 0.0f;
  float last_error_ = 0.0f;
  float lo_ = 0.0f;
  float hi_ = 1.0f;
};
