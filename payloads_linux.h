void HelloWorld_Gnome() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(100);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("gedit");
  delay(1000);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.print("Hello World!!!");
}

void BasicTerminalCommands() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(100);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("gnome-terminal");
  delay(1000);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  delay(3000);
  Keyboard.println("pwd");
  delay(1000);
  Keyboard.println("id");
  delay(1000);
  Keyboard.println("cat /etc/passwd");
}
