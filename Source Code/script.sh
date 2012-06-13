#!/bin/bash
#By Shane_Wayne zx0319@Gmail.com
function count
{
echo -n " Number of matches for $1: "
ls $1|wc -l 
}

