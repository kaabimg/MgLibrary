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
uniform sampler2D qt_Texture0;
varying highp vec2 qt_TexCoord0;

uniform float epsilon = 0.05;
uniform vec4 filterCorlor;


void main()
{
	vec4 color = texture2D(qt_Texture0, qt_TexCoord0);
	
	float diff = abs(color.r - filterCorlor. r) +
			abs(color.g - filterCorlor. g) +
			abs(color.b - filterCorlor. b) +
			abs(color.a - filterCorlor. a);
	
	if(diff < epsilon)
		gl_FragColor = color;
	else
		gl_FragColor = vec4(0,0,0,1);
};