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
attribute highp vec4 qt_Vertex;				
attribute highp vec4 qt_Normal;	
attribute highp vec4 qt_MultiTexCoord0;
uniform mediump mat4 qt_ModelViewProjectionMatrix;
uniform highp vec3 cameraPosition;	

varying vec3 eyeVec;
varying highp vec2 qt_TexCoord0;

vec3 calculateTangentVector(vec3 normal)
{
	vec3 tangent; 

	vec3 c1 = cross(normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(normal, vec3(0.0, 1.0, 0.0)); 

	if(length(c1)>length(c2))
		return normalize(c1);
	else
		return normalize(c2);
}


void main(void)											
{															
	gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;	
										
	qt_TexCoord0 = qt_MultiTexCoord0.xy;
	
	vec3 normal = qt_Normal;
	vec3 tangent = calculateTangentVector(normal);
	vec3 binormal =  cross(normal, tangent);

	vec3 eye = cameraPosition-qt_Vertex.xyz;
	eyeVec.x = dot(eye,tangent);
	eyeVec.y = dot(eye,binormal);
	eyeVec.z = dot(eye,normal);
}	