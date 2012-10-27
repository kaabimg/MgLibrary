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
varying vec3 eyeVec;
uniform vec4 ambiantColor = vec4(0.2,0.2,.2,1);
uniform vec4 diffuseColor =  vec4(0.4,0.4,0.4,1);
uniform float alpha = 1;

void main()													
{	
	vec3 bumpNormal = normalize(texture2D(qt_Texture0, qt_TexCoord0).xyz * 2 -1);
	vec3 eye = normalize(eyeVec);
	float lambertTerm = dot(bumpNormal,eye);
	vec4 Ia = ambiantColor;
	vec4 Id = diffuseColor * lambertTerm ;
	gl_FragColor = clamp(Ia + Id ,0,1);
	gl_FragColor.a = alpha;
}