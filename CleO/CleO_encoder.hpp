int16_t Noop(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 0;
  TX(buf, 2);
  return RX2();
}

int16_t Echo(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 1;
  TX(buf, 2);
  return RX2();
}

int16_t Version(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 2;
  TX(buf, 2);
  return RX2();
}

int16_t ModuleIdentifier(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 3;
  TX(buf, 2);
  return RX2();
}

int16_t UnitIdentifier(
  uint32_t &id0,
  uint32_t &id1)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 4;
  TX(buf, 2);
  RX(10);
  uint8_t *pc;
  pc = c2nbuf + 2;
   id0 = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
   id1 = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t Reboot(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 5;
  TX(buf, 2);
  return RX2();
}

int16_t String(
  int X,
  int Y,
  const char* String)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 256;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  uint8_t *pc = buf + 6;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t String(
  int X,
  double Y,
  const char* String)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 256;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  uint8_t *pc = buf + 6;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t String(
  double X,
  int Y,
  const char* String)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 256;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  uint8_t *pc = buf + 6;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t String(
  double X,
  double Y,
  const char* String)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 256;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  uint8_t *pc = buf + 6;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  int X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  int X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  int X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  int X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  double X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  double X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  double X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringExt(
  int16_t Handle,
  double X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius,
  const char* String)
{
  union{ uint16_t hdr[274/2]; uint8_t buf[274]; };
  hdr[0] = 257;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  uint8_t *pc = buf + 18;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t StringColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 258;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t StringJustification(
  just_t Justification)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 259;
  hdr[1] = Justification;
  TX(buf, 4);
  return RX2();
}

int16_t StringAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 260;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t StringRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 261;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t StringRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 261;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t StringHandle(
  int16_t Handle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 262;
  hdr[1] = Handle;
  TX(buf, 4);
  return RX2();
}

int16_t Bitmap(
  int16_t Handle,
  int X,
  int Y)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 272;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  TX(buf, 8);
  return RX2();
}

int16_t Bitmap(
  int16_t Handle,
  int X,
  double Y)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 272;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  TX(buf, 8);
  return RX2();
}

int16_t Bitmap(
  int16_t Handle,
  double X,
  int Y)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 272;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  TX(buf, 8);
  return RX2();
}

int16_t Bitmap(
  int16_t Handle,
  double X,
  double Y)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 272;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  TX(buf, 8);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  int X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  int X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  int X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  int X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  double X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  double X,
  int Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  double X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  int Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapExt(
  int16_t Handle,
  double X,
  double Y,
  uint32_t Color,
  just_t Justification,
  int16_t Angle,
  double Radius)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 273;
  hdr[1] = Handle;
  hdr[2] = int(8 * X);
  hdr[3] = int(8 * Y);
  hdr[4] = Color;
  hdr[5] = Color >> 16;
  hdr[6] = Justification;
  hdr[7] = Angle;
  hdr[8] = int(8 * Radius);
  TX(buf, 18);
  return RX2();
}

int16_t BitmapColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 274;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t BitmapJustification(
  just_t Justification)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 275;
  hdr[1] = Justification;
  TX(buf, 4);
  return RX2();
}

int16_t BitmapAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 276;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t BitmapRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 277;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t BitmapRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 277;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t BitmapTransform(
  int Scale,
  int16_t Rotate)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 278;
  hdr[1] = int(8 * Scale);
  hdr[2] = Rotate;
  TX(buf, 6);
  return RX2();
}

int16_t BitmapTransform(
  double Scale,
  int16_t Rotate)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 278;
  hdr[1] = int(8 * Scale);
  hdr[2] = Rotate;
  TX(buf, 6);
  return RX2();
}

int16_t Line(
  int x1,
  int y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  int y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  int y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  int y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  double y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  double y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  double y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  int x1,
  double y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  int y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  int y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  int y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  int y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  double y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  double y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  double y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Line(
  double x1,
  double y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 288;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t LineXY(
  int X,
  int Y,
  int Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  int X,
  int Y,
  double Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  int X,
  double Y,
  int Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  int X,
  double Y,
  double Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  double X,
  int Y,
  int Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  double X,
  int Y,
  double Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  double X,
  double Y,
  int Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineXY(
  double X,
  double Y,
  double Length)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 289;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  TX(buf, 8);
  return RX2();
}

int16_t LineExt(
  int x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  int x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineExt(
  double x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 290;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t LineR1R2(
  int x,
  int y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  int y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  int y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  int y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  double y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  double y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  double y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  int x,
  double y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  int y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  int y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  int y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  int y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  double y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  double y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  double y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineR1R2(
  double x,
  double y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 291;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t LineColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 292;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t LineWidth(
  int width)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 293;
  hdr[1] = int(8 * width);
  TX(buf, 4);
  return RX2();
}

int16_t LineWidth(
  double width)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 293;
  hdr[1] = int(8 * width);
  TX(buf, 4);
  return RX2();
}

int16_t LineAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 294;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t LineRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 295;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t LineRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 295;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t Point(
  int x,
  int y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 296;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Point(
  int x,
  double y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 296;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Point(
  double x,
  int y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 296;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Point(
  double x,
  double y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 296;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t PointExt(
  int x,
  int y,
  int radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  int y,
  int radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  int y,
  double radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  int y,
  double radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  double y,
  int radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  double y,
  int radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  double y,
  double radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  int x,
  double y,
  double radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  int y,
  int radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  int y,
  int radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  int y,
  double radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  int y,
  double radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  double y,
  int radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  double y,
  int radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  double y,
  double radius,
  uint32_t color,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointExt(
  double x,
  double y,
  double radius,
  uint32_t color,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 297;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radiusat);
  TX(buf, 16);
  return RX2();
}

int16_t PointRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 298;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t PointRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 298;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t PointAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 299;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t PointAtRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 300;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t PointAtRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 300;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t PointColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 301;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t Circle(
  int x,
  int y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 320;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Circle(
  int x,
  double y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 320;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Circle(
  double x,
  int y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 320;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t Circle(
  double x,
  double y)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 320;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  TX(buf, 6);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  int y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  int x,
  double y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  int y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  int radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  int radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  double radius1,
  int radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleExt(
  double x,
  double y,
  double radius1,
  double radius2,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radiusat)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 321;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radiusat);
  TX(buf, 20);
  return RX2();
}

int16_t CircleR1R2(
  int radius1,
  int radius2)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 322;
  hdr[1] = int(8 * radius1);
  hdr[2] = int(8 * radius2);
  TX(buf, 6);
  return RX2();
}

int16_t CircleR1R2(
  int radius1,
  double radius2)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 322;
  hdr[1] = int(8 * radius1);
  hdr[2] = int(8 * radius2);
  TX(buf, 6);
  return RX2();
}

int16_t CircleR1R2(
  double radius1,
  int radius2)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 322;
  hdr[1] = int(8 * radius1);
  hdr[2] = int(8 * radius2);
  TX(buf, 6);
  return RX2();
}

int16_t CircleR1R2(
  double radius1,
  double radius2)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 322;
  hdr[1] = int(8 * radius1);
  hdr[2] = int(8 * radius2);
  TX(buf, 6);
  return RX2();
}

int16_t CircleAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 323;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t CircleAtRadius(
  int Radiusat)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 324;
  hdr[1] = int(8 * Radiusat);
  TX(buf, 4);
  return RX2();
}

int16_t CircleAtRadius(
  double Radiusat)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 324;
  hdr[1] = int(8 * Radiusat);
  TX(buf, 4);
  return RX2();
}

int16_t CircleColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 325;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t CircleJustification(
  just_t justification)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 326;
  hdr[1] = justification;
  TX(buf, 4);
  return RX2();
}

int16_t RectangleXY(
  int x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  int x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleXY(
  double x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 336;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  int y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  int x,
  double y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  int y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  int width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  int width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  double width,
  int height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleExt(
  double x,
  double y,
  double width,
  double height,
  uint32_t color,
  just_t justification,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[20/2]; uint8_t buf[20]; };
  hdr[0] = 337;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  hdr[5] = color;
  hdr[6] = color >> 16;
  hdr[7] = justification;
  hdr[8] = angle;
  hdr[9] = int(8 * radius);
  TX(buf, 20);
  return RX2();
}

int16_t RectangleColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 338;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t RectangleAngle(
  int16_t Angle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 339;
  hdr[1] = Angle;
  TX(buf, 4);
  return RX2();
}

int16_t RectangleRadius(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 340;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t RectangleRadius(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 340;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t RectangleJustification(
  just_t Justification)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 341;
  hdr[1] = Justification;
  TX(buf, 4);
  return RX2();
}

int16_t RectangleCorner(
  int Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 342;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t RectangleCorner(
  double Radius)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 342;
  hdr[1] = int(8 * Radius);
  TX(buf, 4);
  return RX2();
}

int16_t Needle(
  int x1,
  int y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  int y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  int y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  int y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  double y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  double y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  double y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  int x1,
  double y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  int y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  int y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  int y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  int y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  double y1,
  int x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  double y1,
  int x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  double y1,
  double x2,
  int y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t Needle(
  double x1,
  double y1,
  double x2,
  double y2)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 352;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  int X,
  int Y,
  int Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  int X,
  int Y,
  double Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  int X,
  double Y,
  int Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  int X,
  double Y,
  double Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  double X,
  int Y,
  int Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  double X,
  int Y,
  double Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  double X,
  double Y,
  int Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleXY(
  double X,
  double Y,
  double Length,
  int16_t angle)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 353;
  hdr[1] = int(8 * X);
  hdr[2] = int(8 * Y);
  hdr[3] = int(8 * Length);
  hdr[4] = angle;
  TX(buf, 10);
  return RX2();
}

int16_t NeedleExt(
  int x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  int x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  int y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  int y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  double y,
  int length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  int radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleExt(
  double x,
  double y,
  double length,
  uint32_t color,
  int16_t angle,
  double radius)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 354;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * length);
  hdr[4] = color;
  hdr[5] = color >> 16;
  hdr[6] = angle;
  hdr[7] = int(8 * radius);
  TX(buf, 16);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  int y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  int y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  int y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  int y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  double y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  double y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  double y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  int x,
  double y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  int y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  int y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  int y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  int y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  double y,
  int radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  double y,
  int radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  double y,
  double radius1,
  int radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleR1R2(
  double x,
  double y,
  double radius1,
  double radius2,
  int16_t angle)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 355;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * radius1);
  hdr[4] = int(8 * radius2);
  hdr[5] = angle;
  TX(buf, 12);
  return RX2();
}

int16_t NeedleColor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 356;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t NeedleWidth(
  int width)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 357;
  hdr[1] = int(8 * width);
  TX(buf, 4);
  return RX2();
}

int16_t NeedleWidth(
  double width)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 357;
  hdr[1] = int(8 * width);
  TX(buf, 4);
  return RX2();
}

int16_t SetBackgroundcolor(
  uint32_t argb)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 368;
  hdr[1] = argb;
  hdr[2] = argb >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  int y1,
  int x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  int y1,
  int x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  int y1,
  double x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  int y1,
  double x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  double y1,
  int x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  double y1,
  int x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  double y1,
  double x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  int x1,
  double y1,
  double x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  int y1,
  int x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  int y1,
  int x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  int y1,
  double x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  int y1,
  double x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  double y1,
  int x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  double y1,
  int x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  double y1,
  double x2,
  int y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundGradient(
  double x1,
  double y1,
  double x2,
  double y2,
  uint32_t rgb1,
  uint32_t rgb2)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 369;
  hdr[1] = int(8 * x1);
  hdr[2] = int(8 * y1);
  hdr[3] = int(8 * x2);
  hdr[4] = int(8 * y2);
  hdr[5] = rgb1;
  hdr[6] = rgb1 >> 16;
  hdr[7] = rgb2;
  hdr[8] = rgb2 >> 16;
  TX(buf, 18);
  return RX2();
}

int16_t SetBackgroundImage(
  int16_t Handle,
  int16_t mode)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 370;
  hdr[1] = Handle;
  hdr[2] = mode;
  TX(buf, 6);
  return RX2();
}

int16_t SetBackgroundVideo(
  const char* FileName,
  int16_t framerate)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 371;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = framerate; *pc++ = framerate >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t SetAngleType(
  int16_t AngleType)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 372;
  hdr[1] = AngleType;
  TX(buf, 4);
  return RX2();
}

int16_t SetDefaultContext(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 373;
  TX(buf, 2);
  return RX2();
}

int16_t Scissor(
  int x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  int x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Scissor(
  double x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 374;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Start(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 384;
  TX(buf, 2);
  return RX2();
}

int16_t Show(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 385;
  TX(buf, 2);
  return RX2();
}

int16_t Sound(
  int16_t Sound)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 592;
  hdr[1] = Sound;
  TX(buf, 4);
  return RX2();
}

int16_t SoundExt(
  int16_t Sound,
  int16_t pitch,
  int16_t volume,
  int16_t duration)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 593;
  hdr[1] = Sound;
  hdr[2] = pitch;
  hdr[3] = volume;
  hdr[4] = duration;
  TX(buf, 10);
  return RX2();
}

int16_t SoundVol(
  int16_t Volume)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 594;
  hdr[1] = Volume;
  TX(buf, 4);
  return RX2();
}

int16_t SoundDuration(
  int16_t Duration)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 595;
  hdr[1] = Duration;
  TX(buf, 4);
  return RX2();
}

int16_t SetSound(
  int16_t Sound,
  int16_t pitch,
  int16_t volume,
  int16_t duration)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 596;
  hdr[1] = Sound;
  hdr[2] = pitch;
  hdr[3] = volume;
  hdr[4] = duration;
  TX(buf, 10);
  return RX2();
}

int16_t SoundPlay(
  int16_t play)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 597;
  hdr[1] = play;
  TX(buf, 4);
  return RX2();
}

int16_t AudioPlay(
  const char* Filename,
  int16_t mode)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 598;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, Filename);
  *pc++ = mode; *pc++ = mode >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t AudioStop(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 599;
  TX(buf, 2);
  return RX2();
}

int16_t MPlay(
  int16_t Instrument,
  int16_t Delay,
  const char* String)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 600;
  hdr[1] = Instrument;
  hdr[2] = Delay;
  uint8_t *pc = buf + 6;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t Tag(
  int16_t Tag)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 768;
  hdr[1] = Tag;
  TX(buf, 4);
  return RX2();
}

int16_t EnableTag(
  int16_t Enable)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 769;
  hdr[1] = Enable;
  TX(buf, 4);
  return RX2();
}

int16_t TouchCoordinates(
  int16_t &touchx,
  int16_t &touchy,
  int16_t &touchdur,
  int16_t &touchtag)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 770;
  TX(buf, 2);
  RX(10);
  uint8_t *pc;
  pc = c2nbuf + 2;
   touchx = pc[0] | (pc[1] << 8); pc += 2;
   touchy = pc[0] | (pc[1] << 8); pc += 2;
   touchdur = pc[0] | (pc[1] << 8); pc += 2;
   touchtag = pc[0] | (pc[1] << 8); pc += 2;
  return c2nbuf_w[0];
}

int16_t ColorPicker(
  const char* prompt,
  uint32_t &argb)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 848;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, prompt);
  *pc++ = argb; *pc++ = argb >> 8; *pc++ = argb >> 16; *pc++ = argb >> 24;
  TX(buf, pc - buf);
  RX(6);
  pc = c2nbuf + 2;
   argb = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t SetDateTime(
  const char* prompt,
  uint32_t &epoch)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 849;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, prompt);
  *pc++ = epoch; *pc++ = epoch >> 8; *pc++ = epoch >> 16; *pc++ = epoch >> 24;
  TX(buf, pc - buf);
  RX(6);
  pc = c2nbuf + 2;
   epoch = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t Keyboard(
  const char* prompt,
  textfield &AlphaNumeric)
{
  union{ uint16_t hdr[290/2]; uint8_t buf[290]; };
  hdr[0] = 850;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, prompt);
  memcpy((char*)pc, (const char*)&AlphaNumeric, sizeof(textfield)); pc += sizeof(textfield);
  TX(buf, pc - buf);
  RX(34);
  pc = c2nbuf + 2;
   AlphaNumeric = *(textfield*)pc; pc += sizeof(textfield);
  return c2nbuf_w[0];
}

int16_t KeyPad(
  const char* prompt,
  int16_t Numeric)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 851;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, prompt);
  *pc++ = Numeric; *pc++ = Numeric >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  int x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t CaptureScreen(
  const char* FileName,
  double x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 852;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = int(8 * x); *pc++ = int(8 * x) >> 8;
  *pc++ = int(8 * y); *pc++ = int(8 * y) >> 8;
  *pc++ = int(8 * width); *pc++ = int(8 * width) >> 8;
  *pc++ = int(8 * height); *pc++ = int(8 * height) >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t LoadFont(
  const char* FileName)
{
  union{ uint16_t hdr[258/2]; uint8_t buf[258]; };
  hdr[0] = 853;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  TX(buf, pc - buf);
  return RX2();
}

int16_t LoadImageFile(
  const char* FileName,
  int16_t format)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 854;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = format; *pc++ = format >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t LoadIcon(
  const char* FileName,
  int16_t index)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 855;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  *pc++ = index; *pc++ = index >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t Sketch(
  int x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  int x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  int y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  int y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  int y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  int y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  double y,
  int width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  double y,
  int width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  double y,
  double width,
  int height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t Sketch(
  double x,
  double y,
  double width,
  double height)
{
  union{ uint16_t hdr[10/2]; uint8_t buf[10]; };
  hdr[0] = 856;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = int(8 * width);
  hdr[4] = int(8 * height);
  TX(buf, 10);
  return RX2();
}

int16_t LoadAudioFile(
  const char* FileName)
{
  union{ uint16_t hdr[258/2]; uint8_t buf[258]; };
  hdr[0] = 857;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  TX(buf, pc - buf);
  return RX2();
}

int16_t LoadVideoFile(
  const char* FileName)
{
  union{ uint16_t hdr[258/2]; uint8_t buf[258]; };
  hdr[0] = 858;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  TX(buf, pc - buf);
  return RX2();
}

int16_t Free(
  int16_t Handle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 859;
  hdr[1] = Handle;
  TX(buf, 4);
  return RX2();
}

int16_t Calibration(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 860;
  TX(buf, 2);
  return RX2();
}

int16_t EpochToDate(
  uint32_t epoch,
  int16_t &year,
  int16_t &mon,
  int16_t &mday,
  int16_t &hour,
  int16_t &mins,
  int16_t &sec,
  int16_t &wday)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 861;
  hdr[1] = epoch;
  hdr[2] = epoch >> 16;
  TX(buf, 6);
  RX(16);
  uint8_t *pc;
  pc = c2nbuf + 2;
   year = pc[0] | (pc[1] << 8); pc += 2;
   mon = pc[0] | (pc[1] << 8); pc += 2;
   mday = pc[0] | (pc[1] << 8); pc += 2;
   hour = pc[0] | (pc[1] << 8); pc += 2;
   mins = pc[0] | (pc[1] << 8); pc += 2;
   sec = pc[0] | (pc[1] << 8); pc += 2;
   wday = pc[0] | (pc[1] << 8); pc += 2;
  return c2nbuf_w[0];
}

int16_t DateToEpoch(
  uint32_t &epoch,
  int16_t year,
  int16_t mon,
  int16_t mday,
  int16_t hour,
  int16_t mins,
  int16_t sec)
{
  union{ uint16_t hdr[14/2]; uint8_t buf[14]; };
  hdr[0] = 862;
  hdr[1] = year;
  hdr[2] = mon;
  hdr[3] = mday;
  hdr[4] = hour;
  hdr[5] = mins;
  hdr[6] = sec;
  TX(buf, 14);
  RX(6);
  uint8_t *pc;
  pc = c2nbuf + 2;
   epoch = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t CRCScreen(
  uint32_t &crc32)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 863;
  TX(buf, 2);
  RX(6);
  uint8_t *pc;
  pc = c2nbuf + 2;
   crc32 = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t SetErrorTrap(
  int16_t enable)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 864;
  hdr[1] = enable;
  TX(buf, 4);
  return RX2();
}

int16_t Display(
  int16_t On)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1024;
  hdr[1] = On;
  TX(buf, 4);
  return RX2();
}

int16_t DisplayRotate(
  int16_t rotation,
  int16_t flip)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 1025;
  hdr[1] = rotation;
  hdr[2] = flip;
  TX(buf, 6);
  return RX2();
}

int16_t CameraLEDS(
  int16_t On)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1026;
  hdr[1] = On;
  TX(buf, 4);
  return RX2();
}

int16_t FOpen(
  const char* String,
  int16_t mode)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 1280;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, String);
  *pc++ = mode; *pc++ = mode >> 8;
  TX(buf, pc - buf);
  return RX2();
}

int16_t FClose(
  int16_t handle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1281;
  hdr[1] = handle;
  TX(buf, 4);
  return RX2();
}

int16_t FRead(
  int16_t Handle,
  uint8_t* Buffer,
  int16_t bytestoread,
  int16_t & bytesread)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 1282;
  hdr[1] = Handle;
  hdr[2] = bytestoread;
  TX(buf, 6);
  RX(4 + bytestoread);
  bytesread = c2nbuf_w[1];
  memcpy(Buffer, c2nbuf + 4, bytesread);
  return c2nbuf_w[0];
}

int16_t FWrite(
  int16_t Handle,
  int16_t bytestowrite,
  uint8_t* Buffer,
  int16_t &byteswritten)
{
  union{ uint16_t hdr[262/2]; uint8_t buf[262]; };
  hdr[0] = 1283;
  hdr[1] = Handle;
  hdr[2] = bytestowrite;
  uint8_t *pc = buf + 6;
  memcpy((char*)pc, (const char*)Buffer, bytestowrite); pc += bytestowrite;
  TX(buf, pc - buf);
  RX(4);
  pc = c2nbuf + 2;
   byteswritten = pc[0] | (pc[1] << 8); pc += 2;
  return c2nbuf_w[0];
}

int16_t FSeek(
  int16_t Handle,
  uint32_t Offset)
{
  union{ uint16_t hdr[8/2]; uint8_t buf[8]; };
  hdr[0] = 1284;
  hdr[1] = Handle;
  hdr[2] = Offset;
  hdr[3] = Offset >> 16;
  TX(buf, 8);
  return RX2();
}

int16_t FGetS(
  int16_t Handle,
  uint8_t* Buffer,
  int16_t buflen)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 1285;
  hdr[1] = Handle;
  hdr[2] = buflen;
  TX(buf, 6);
  RX(2 + buflen);
  memcpy(Buffer, c2nbuf + 2, buflen);
  return c2nbuf_w[0];
}

int16_t FPutS(
  int16_t Handle,
  const char* String)
{
  union{ uint16_t hdr[260/2]; uint8_t buf[260]; };
  hdr[0] = 1286;
  hdr[1] = Handle;
  uint8_t *pc = buf + 4;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t FGetC(
  int16_t Handle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1287;
  hdr[1] = Handle;
  TX(buf, 4);
  return RX2();
}

int16_t FPutC(
  int16_t Handle,
  int16_t Character)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 1288;
  hdr[1] = Handle;
  hdr[2] = Character;
  TX(buf, 6);
  return RX2();
}

int16_t FTell(
  int16_t Handle,
  uint32_t &Offset)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1289;
  hdr[1] = Handle;
  TX(buf, 4);
  RX(6);
  uint8_t *pc;
  pc = c2nbuf + 2;
   Offset = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t FEOF(
  int16_t Handle)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1290;
  hdr[1] = Handle;
  TX(buf, 4);
  return RX2();
}

int16_t FSize(
  int16_t Handle,
  uint32_t &Offset)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1291;
  hdr[1] = Handle;
  TX(buf, 4);
  RX(6);
  uint8_t *pc;
  pc = c2nbuf + 2;
   Offset = pc[0] | ((uint32_t)pc[1] << 8) | ((uint32_t)pc[2] << 16) | ((uint32_t)pc[3] << 24); pc += 4;
  return c2nbuf_w[0];
}

int16_t InternalEFlashUpdate(
  int16_t Handle,
  int16_t Code)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 1292;
  hdr[1] = Handle;
  hdr[2] = Code;
  TX(buf, 6);
  return RX2();
}

int16_t PlayerPlay(
  int16_t Play)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1872;
  hdr[1] = Play;
  TX(buf, 4);
  return RX2();
}

int16_t GetPlayerProperties(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 1873;
  TX(buf, 2);
  return RX2();
}

int16_t PlayerExit(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 1874;
  TX(buf, 2);
  return RX2();
}

int16_t SetRecorderProperties(
  const char* FileName)
{
  union{ uint16_t hdr[258/2]; uint8_t buf[258]; };
  hdr[0] = 1888;
  uint8_t *pc = buf + 2;
  pc = addstr(pc, FileName);
  TX(buf, pc - buf);
  return RX2();
}

int16_t GetRecorderProperties(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 1889;
  TX(buf, 2);
  return RX2();
}

int16_t RecorderPreview(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 1890;
  TX(buf, 2);
  return RX2();
}

int16_t RecorderRecord(
  int16_t Start)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1891;
  hdr[1] = Start;
  TX(buf, 4);
  return RX2();
}

int16_t RecorderCapture(
  int16_t NumofPictures)
{
  union{ uint16_t hdr[4/2]; uint8_t buf[4]; };
  hdr[0] = 1892;
  hdr[1] = NumofPictures;
  TX(buf, 4);
  return RX2();
}

int16_t eve_bgcolor(
  uint32_t c)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 2048;
  hdr[1] = c;
  hdr[2] = c >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t eve_button(
  int x,
  int y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2049;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_button(
  int x,
  double y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2049;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_button(
  double x,
  int y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2049;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_button(
  double x,
  double y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2049;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_clock(
  int x,
  int y,
  int16_t r,
  int16_t options,
  int16_t h,
  int16_t m,
  int16_t s,
  int16_t ms)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2050;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = h;
  hdr[6] = m;
  hdr[7] = s;
  hdr[8] = ms;
  TX(buf, 18);
  return RX2();
}

int16_t eve_clock(
  int x,
  double y,
  int16_t r,
  int16_t options,
  int16_t h,
  int16_t m,
  int16_t s,
  int16_t ms)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2050;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = h;
  hdr[6] = m;
  hdr[7] = s;
  hdr[8] = ms;
  TX(buf, 18);
  return RX2();
}

int16_t eve_clock(
  double x,
  int y,
  int16_t r,
  int16_t options,
  int16_t h,
  int16_t m,
  int16_t s,
  int16_t ms)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2050;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = h;
  hdr[6] = m;
  hdr[7] = s;
  hdr[8] = ms;
  TX(buf, 18);
  return RX2();
}

int16_t eve_clock(
  double x,
  double y,
  int16_t r,
  int16_t options,
  int16_t h,
  int16_t m,
  int16_t s,
  int16_t ms)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2050;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = h;
  hdr[6] = m;
  hdr[7] = s;
  hdr[8] = ms;
  TX(buf, 18);
  return RX2();
}

int16_t eve_coldstart(
)
{
  union{ uint16_t hdr[2/2]; uint8_t buf[2]; };
  hdr[0] = 2051;
  TX(buf, 2);
  return RX2();
}

int16_t eve_dial(
  int x,
  int y,
  int16_t r,
  int16_t options,
  int16_t val)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 2052;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = val;
  TX(buf, 12);
  return RX2();
}

int16_t eve_dial(
  int x,
  double y,
  int16_t r,
  int16_t options,
  int16_t val)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 2052;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = val;
  TX(buf, 12);
  return RX2();
}

int16_t eve_dial(
  double x,
  int y,
  int16_t r,
  int16_t options,
  int16_t val)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 2052;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = val;
  TX(buf, 12);
  return RX2();
}

int16_t eve_dial(
  double x,
  double y,
  int16_t r,
  int16_t options,
  int16_t val)
{
  union{ uint16_t hdr[12/2]; uint8_t buf[12]; };
  hdr[0] = 2052;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = val;
  TX(buf, 12);
  return RX2();
}

int16_t eve_fgcolor(
  uint32_t c)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 2053;
  hdr[1] = c;
  hdr[2] = c >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t eve_gauge(
  int x,
  int y,
  int16_t r,
  int16_t options,
  int16_t major,
  int16_t minor,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2054;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = major;
  hdr[6] = minor;
  hdr[7] = val;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_gauge(
  int x,
  double y,
  int16_t r,
  int16_t options,
  int16_t major,
  int16_t minor,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2054;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = major;
  hdr[6] = minor;
  hdr[7] = val;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_gauge(
  double x,
  int y,
  int16_t r,
  int16_t options,
  int16_t major,
  int16_t minor,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2054;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = major;
  hdr[6] = minor;
  hdr[7] = val;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_gauge(
  double x,
  double y,
  int16_t r,
  int16_t options,
  int16_t major,
  int16_t minor,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2054;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = r;
  hdr[4] = options;
  hdr[5] = major;
  hdr[6] = minor;
  hdr[7] = val;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_gradcolor(
  uint32_t c)
{
  union{ uint16_t hdr[6/2]; uint8_t buf[6]; };
  hdr[0] = 2055;
  hdr[1] = c;
  hdr[2] = c >> 16;
  TX(buf, 6);
  return RX2();
}

int16_t eve_keys(
  int x,
  int y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2056;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_keys(
  int x,
  double y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2056;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_keys(
  double x,
  int y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2056;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_keys(
  double x,
  double y,
  int16_t w,
  int16_t h,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2056;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = font;
  hdr[6] = options;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_number(
  int x,
  int y,
  int16_t font,
  int16_t options,
  int32_t n)
{
  union{ uint16_t hdr[14/2]; uint8_t buf[14]; };
  hdr[0] = 2057;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  *pc++ = n; *pc++ = n >> 8; *pc++ = n >> 16; *pc++ = n >> 24;
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_number(
  int x,
  double y,
  int16_t font,
  int16_t options,
  int32_t n)
{
  union{ uint16_t hdr[14/2]; uint8_t buf[14]; };
  hdr[0] = 2057;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  *pc++ = n; *pc++ = n >> 8; *pc++ = n >> 16; *pc++ = n >> 24;
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_number(
  double x,
  int y,
  int16_t font,
  int16_t options,
  int32_t n)
{
  union{ uint16_t hdr[14/2]; uint8_t buf[14]; };
  hdr[0] = 2057;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  *pc++ = n; *pc++ = n >> 8; *pc++ = n >> 16; *pc++ = n >> 24;
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_number(
  double x,
  double y,
  int16_t font,
  int16_t options,
  int32_t n)
{
  union{ uint16_t hdr[14/2]; uint8_t buf[14]; };
  hdr[0] = 2057;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  *pc++ = n; *pc++ = n >> 8; *pc++ = n >> 16; *pc++ = n >> 24;
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_progress(
  int x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2058;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_progress(
  int x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2058;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_progress(
  double x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2058;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_progress(
  double x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2058;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_scrollbar(
  int x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t size,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2059;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = size;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_scrollbar(
  int x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t size,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2059;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = size;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_scrollbar(
  double x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t size,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2059;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = size;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_scrollbar(
  double x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t size,
  int16_t range)
{
  union{ uint16_t hdr[18/2]; uint8_t buf[18]; };
  hdr[0] = 2059;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = size;
  hdr[8] = range;
  TX(buf, 18);
  return RX2();
}

int16_t eve_slider(
  int x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2060;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_slider(
  int x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2060;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_slider(
  double x,
  int y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2060;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_slider(
  double x,
  double y,
  int16_t w,
  int16_t h,
  int16_t options,
  int16_t val,
  int16_t range)
{
  union{ uint16_t hdr[16/2]; uint8_t buf[16]; };
  hdr[0] = 2060;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = h;
  hdr[5] = options;
  hdr[6] = val;
  hdr[7] = range;
  TX(buf, 16);
  return RX2();
}

int16_t eve_text(
  int x,
  int y,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 2061;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_text(
  int x,
  double y,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 2061;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_text(
  double x,
  int y,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 2061;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_text(
  double x,
  double y,
  int16_t font,
  int16_t options,
  const char* String)
{
  union{ uint16_t hdr[266/2]; uint8_t buf[266]; };
  hdr[0] = 2061;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = font;
  hdr[4] = options;
  uint8_t *pc = buf + 10;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_toggle(
  int x,
  int y,
  int16_t w,
  int16_t font,
  int16_t options,
  int16_t state,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2062;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = font;
  hdr[5] = options;
  hdr[6] = state;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_toggle(
  int x,
  double y,
  int16_t w,
  int16_t font,
  int16_t options,
  int16_t state,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2062;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = font;
  hdr[5] = options;
  hdr[6] = state;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_toggle(
  double x,
  int y,
  int16_t w,
  int16_t font,
  int16_t options,
  int16_t state,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2062;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = font;
  hdr[5] = options;
  hdr[6] = state;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

int16_t eve_toggle(
  double x,
  double y,
  int16_t w,
  int16_t font,
  int16_t options,
  int16_t state,
  const char* String)
{
  union{ uint16_t hdr[270/2]; uint8_t buf[270]; };
  hdr[0] = 2062;
  hdr[1] = int(8 * x);
  hdr[2] = int(8 * y);
  hdr[3] = w;
  hdr[4] = font;
  hdr[5] = options;
  hdr[6] = state;
  uint8_t *pc = buf + 14;
  pc = addstr(pc, String);
  TX(buf, pc - buf);
  return RX2();
}

