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
uniform int width;
uniform int height;
uniform float factor=2; 
uniform sampler2D qt_Texture0;
varying vec2 qt_TexCoord0;
//TODO: te rework
void main(void)
{
    
    vec2 Tile = vec2(factor/width,factor/height);
    vec2 Blur = vec2(0.3,0.3);
    // Current texture position (normalised)
    vec2 texCoord = qt_TexCoord0.xy;
    // Normalised position of current pixel in its tile
    vec2 tilePos = vec2(fract(texCoord.x / Tile.x), fract(texCoord.y / Tile.y));
    
    // Bottom-left of current tile
    vec2 p0 = vec2(floor(texCoord.x / Tile.x) * Tile.x, floor(texCoord.y / Tile.y) * Tile.y);
    // Bottom-left of tile to Left of current tile
    vec2 p1 = vec2(clamp(p0.x - Tile.x, 0.0, 1.0), p0.y);
    // Bottom-left of tile Below current tile
    vec2 p2 = vec2(p0.x, clamp(p0.y - Tile.y, 0.0, 1.0));
    // Bottom-left of tile Below and Left of current tile
    vec2 p3 = vec2(p1.x, p2.y);

    vec2 mixFactors;
    mixFactors.x =  min(tilePos.x / Blur.x, 1.0);
    mixFactors.y =  min(tilePos.y / Blur.y, 1.0);

    vec4 tmp1 = mix(texture2D(qt_Texture0, p1+(Tile/2.0)), texture2D(qt_Texture0, p0+(Tile/2.0)), mixFactors.x);
    vec4 tmp2 = mix(texture2D(qt_Texture0, p3 +(Tile/2.0)), texture2D(qt_Texture0, p2+(Tile/2.0)), mixFactors.x);
    gl_FragColor = mix(tmp2, tmp1, mixFactors.y);
}