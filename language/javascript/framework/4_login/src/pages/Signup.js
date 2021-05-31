import React, { useState } from "react";

export default function Signup(props) {
  const [form, setForm] = useState({
    username: "",
    email: "",
    password: "",
    confirm: "",
  });

  const handleChange = (e) => {
    setForm({
      ...form,
      [e.target.id]: e.target.value,
    });
  };

  return (
    <form onSubmit={() => props.signup(form)}>
      <label>Username</label>
      <input
        type="text"
        required
        id="username"
        value={form.username}
        onChange={handleChange}
      />
      <label>Email</label>
      <input
        type="text"
        required
        id="email"
        value={form.email}
        onChange={handleChange}
      />
      <label>Password</label>
      <input
        type="text"
        id="password"
        required
        value={form.password}
        onChange={handleChange}
      />
      <label>Confirm Password</label>
      <input
        type="text"
        id="confirm"
        required
        value={form.confirm}
        onChange={handleChange}
      />
      <button type="submit">Register</button>
    </form>
  );
}
