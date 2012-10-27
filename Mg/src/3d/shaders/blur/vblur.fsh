/*************************************************************************
** 
** Copyright 2011 Mohamed-Ghaïth KAABI (mohamedghaith.kaabi@gmail.com)
** This file is part of MgLibrary.
** 
** MgLibrary is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** any later version.
** 
** MgLibrary is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with MgLibrary.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
uniform sampler2D texture; 
varying vec2 qt_TexCoord0;
uniform float blurSize;
 
void main(void)
{
   vec4 sum = vec4(0.0);
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y - blurSize)) * 0.15;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y)) * 0.16;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y + blurSize)) * 0.15;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(texture, vec2(qt_TexCoord0.x, qt_TexCoord0.y + 4.0*blurSize)) * 0.05;
 
   gl_FragColor = sum;
}